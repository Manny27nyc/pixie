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

#include <stdint.h>

namespace px {
namespace stirling {

class JavaRawSymbolUpdate {
 public:
  uint64_t addr;
  uint64_t code_size;
  uint64_t symbol_size;
  uint64_t fn_sig_size;
  uint64_t class_sig_size;
  bool method_unload;

  uint64_t TotalNumSymbolBytes() const { return symbol_size + fn_sig_size + class_sig_size; }
  uint64_t SymbolOffset() const { return 0; }
  uint64_t FnSigOffset() const { return symbol_size; }
  uint64_t ClassSigOffset() const { return symbol_size + fn_sig_size; }
  bool IsMethodUnload() const { return method_unload; }
};

}  // namespace stirling
}  // namespace px
