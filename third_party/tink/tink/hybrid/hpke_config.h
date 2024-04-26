// Copyright 2021 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef TINK_HYBRID_HPKE_CONFIG_H_
#define TINK_HYBRID_HPKE_CONFIG_H_

#include "tink/util/status.h"

namespace crypto {
namespace tink {

// Registers HybridEncrypt and HybridDecrypt primitive wrappers, and key
// managers for HPKE Encrypt and HPKE Decrypt from the current Tink release.
crypto::tink::util::Status RegisterHpke();

}  // namespace tink
}  // namespace crypto

#endif  // TINK_HYBRID_HPKE_CONFIG_H_
