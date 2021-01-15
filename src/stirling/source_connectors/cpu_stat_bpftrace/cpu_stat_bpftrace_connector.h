#pragma once

#include <memory>
#include <string>
#include <vector>

#include "src/stirling/core/source_connector.h"

#ifndef __linux__
namespace pl {
namespace stirling {

DUMMY_SOURCE_CONNECTOR(CPUStatBPFTraceConnector);

}  // namespace stirling
}  // namespace pl
#else

#include "src/common/base/base.h"
#include "src/stirling/bpf_tools/bpftrace_wrapper.h"

namespace pl {
namespace stirling {

class CPUStatBPFTraceConnector : public SourceConnector, public bpf_tools::BPFTraceWrapper {
 public:
  // clang-format off
  static constexpr DataElement kElements[] = {
      {
        "time_",
        "Timestamp when the data record was collected.",
        types::DataType::TIME64NS,
        types::SemanticType::ST_NONE,
        types::PatternType::METRIC_COUNTER
      },
      {
        "cpustat_user",
        "",
        types::DataType::INT64,
        types::SemanticType::ST_NONE,
        types::PatternType::METRIC_COUNTER
      },
      {
        "cpustat_nice",
        "",
        types::DataType::INT64,
        types::SemanticType::ST_NONE,
        types::PatternType::METRIC_COUNTER
      },
      {
        "cpustat_system",
        "",
        types::DataType::INT64,
        types::SemanticType::ST_NONE,
        types::PatternType::METRIC_COUNTER
      },
      {
        "cpustat_idle",
        "",
        types::DataType::INT64,
        types::SemanticType::ST_NONE,
        types::PatternType::METRIC_COUNTER
      },
      {
        "cpustat_iowait",
        "",
        types::DataType::INT64,
        types::SemanticType::ST_NONE,
        types::PatternType::METRIC_COUNTER
      },
      {
        "cpustat_irq",
        "",
        types::DataType::INT64,
        types::SemanticType::ST_NONE,
        types::PatternType::METRIC_COUNTER
      },
      {
        "cpustat_softirq",
        "",
        types::DataType::INT64,
        types::SemanticType::ST_NONE,
        types::PatternType::METRIC_COUNTER
      }
  };
  // clang-format on
  static constexpr auto kTable =
      DataTableSchema("bpftrace_cpu_stats", kElements, std::chrono::milliseconds{100},
                      std::chrono::milliseconds{1000});
  static constexpr auto kTables = MakeArray(kTable);

  static std::unique_ptr<SourceConnector> Create(std::string_view name) {
    // TODO(oazizi): Expose cpu_id through Create.
    return std::unique_ptr<SourceConnector>(new CPUStatBPFTraceConnector(name, /* cpu_id */ 0));
  }

  Status InitImpl() override;
  Status StopImpl() override;
  void TransferDataImpl(ConnectorContext* ctx, uint32_t table_num, DataTable* data_table) override;

 protected:
  CPUStatBPFTraceConnector(std::string_view name, uint64_t cpu_id)
      : SourceConnector(name, kTables), cpu_id_(cpu_id) {}

 private:
  uint64_t cpu_id_ = 0;
};

}  // namespace stirling
}  // namespace pl

#endif