/*
 * Copyright 2018- The Pixie Authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <list>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "src/stirling/source_connectors/socket_tracer/conn_tracker.h"
#include "src/stirling/utils/obj_pool.h"

namespace px {
namespace stirling {

using ConnTrackerPool = ObjPool<ConnTracker>;

/**
 * ConnTrackersGenerations is a container of tracker generations,
 * where a generation is identified by the timestamp ID (TSID).
 *
 * It automatically handles marking older generations for death.
 */
class ConnTrackerGenerations {
 public:
  /**
   * Get ConnTracker by TSID, or return a new one if the TSID does not exist.
   *
   * @return The pointer to the conn_tracker and whether the tracker was newly created.
   */
  std::pair<ConnTracker*, bool> GetOrCreate(uint64_t tsid, ConnTrackerPool* tracker_pool);

  bool Contains(uint64_t tsid) const;

  /**
   * Returns the oldest tracker, or error if the oldest tracker either has been destroyed
   * or is ReadyForDestruction().
   */
  StatusOr<const ConnTracker*> GetActive() const;

  bool empty() const { return generations_.empty(); }

  /**
   * Removes all trackers that are ReadyForDestruction().
   * Removed trackers are pushed into the tracker pool for recycling.
   */
  int CleanupGenerations(ConnTrackerPool* tracker_pool);

 private:
  // A map of TSID to ConnTrackers.
  absl::flat_hash_map<uint64_t, std::unique_ptr<ConnTracker>> generations_;

  // Keep a pointer to the ConnTracker generation with the highest TSID.
  ConnTracker* oldest_generation_ = nullptr;

  friend class ConnTrackerGenerationsTest;
};

/**
 * ConnTrackersManager is a container that keeps track of all ConnTrackers.
 * Interface designed for two primary operations:
 *  1) Insertion of events indexed by conn_id (PID+FD+TSID) as they arrive from BPF.
 *  2) Iteration through trackers by protocols.
 */
class ConnTrackersManager {
 public:
  ConnTrackersManager();

  /**
   * Get a connection tracker for the specified conn_id. If a tracker does not exist,
   * one will be created and returned.
   */
  ConnTracker& GetOrCreateConnTracker(struct conn_id_t conn_id);

  /**
   * A TrackersList consists of a list of trackers.
   * It can only be created via ConnTrackersForProtocol(), such that it returns a list
   * of trackers that have the requested protocol.
   *
   * Usage model example:
   * ConnTrackersManager::TrackersList http_conn_trackers =
   *     conn_trackers_mgr.ConnTrackersForProtocol(kProtocolHTTP);
   *
   * for (auto iter = http_conn_trackers.begin(); iter != http_conn_trackers.end(); ++iter) {
   *   ConnTracker* tracker = *iter;
   *
   *   // Relevant actions on tracker go here.
   * }
   */
  class TrackersList {
   public:
    /**
     * A custom iterator for going through the list of trackers for a given protocol.
     * This iterator automatically handles removing trackers whose protocol has changed
     * (currently this should only be possible from kProtocolUnknown), and the removal of
     * trackers that are ReadyForDestruction().
     */
    class TrackersListIterator {
     public:
      bool operator!=(const TrackersListIterator& other);

      ConnTracker* operator*();

      // Prefix increment operator.
      TrackersListIterator operator++();

     private:
      TrackersListIterator(std::list<ConnTracker*>* trackers,
                           std::list<ConnTracker*>::iterator iter,
                           ConnTrackersManager* conn_trackers_manager);

      std::list<ConnTracker*>* trackers_;
      std::list<ConnTracker*>::iterator iter_;
      ConnTrackersManager* conn_trackers_manager_;

      friend class TrackersList;
    };

    TrackersListIterator begin() {
      return TrackersListIterator(list_, list_->begin(), conn_trackers_);
    }

    TrackersListIterator end() { return TrackersListIterator(list_, list_->end(), conn_trackers_); }

   private:
    TrackersList(std::list<ConnTracker*>* list, ConnTrackersManager* conn_trackers)
        : list_(list), conn_trackers_(conn_trackers) {}

    std::list<ConnTracker*>* list_;
    ConnTrackersManager* conn_trackers_;

    friend class ConnTrackersManager;
  };

  /**
   * Returns a list of all the trackers that belong to a particular protocol.
   */
  TrackersList ConnTrackersForProtocol(TrafficProtocol protocol) {
    return TrackersList(&conn_trackers_by_protocol_[protocol], this);
  }

  /**
   * Returns the latest generation of a connection tracker for the given pid and fd.
   * If there is no tracker for {pid, fd}, returns error::NotFound.
   */
  StatusOr<const ConnTracker*> GetConnTracker(uint32_t pid, uint32_t fd) const;

  /**
   * If a connection tracker has its protocol changed, then one must manually call this function.
   * TODO(oazizi): Find a cleaner/more automatic way that can avoid this call altogether.
   */
  void UpdateProtocol(ConnTracker* tracker, std::optional<TrafficProtocol> old_protocol);

  /**
   * Deletes trackers that are ReadyForDestruction().
   * Call this only after accumulating enough trackers to clean-up, to avoid the performance
   * impact of scanning through all trackers every iteration.
   */
  void CleanupTrackers();

  /**
   * Checks the consistency of the data structures.
   * Useful for catching bugs. Meant for use in testing.
   * Could be expensive if called too regularly in production.
   * See DebugChecks() for simpler checks that can be used in production.
   */
  Status TestOnlyCheckConsistency() const;

  /**
   * Returns extensive debug information about the connection trackers.
   */
  std::string DebugInfo() const;

 private:
  // Simple consistency DCHECKs meant for enforcing invariants.
  void DebugChecks() const;

  // A map from conn_id (PID+FD+TSID) to tracker. This is for easy update on BPF events.
  // Structured as two nested maps to be explicit about "generations" of trackers per PID+FD.
  // Key is {PID, FD} for outer map, and tsid for inner map.
  absl::flat_hash_map<uint64_t, ConnTrackerGenerations> conn_trackers_;

  // A set of lists of pointers to all the contained trackers, organized by protocol
  // This is for easy access to the trackers during TransferData().
  // Key is protocol.
  // TODO(jps): Convert to vector?
  absl::flat_hash_map<TrafficProtocol, std::list<ConnTracker*>> conn_trackers_by_protocol_;

  // Keep track of total number of trackers, and other counts.
  // Used to check for consistency.
  size_t num_trackers_ = 0;
  size_t num_trackers_ready_for_destruction_ = 0;
  size_t num_trackers_in_lists_ = 0;

  // A pool of unused trackers that can be recycled.
  // This is useful for avoiding memory reallocations.
  ConnTrackerPool trackers_pool_;
};

}  // namespace stirling
}  // namespace px
