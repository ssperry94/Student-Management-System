// Copyright 2018 Google Inc.
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

#ifndef TINK_DAEAD_DETERMINISTIC_AEAD_FACTORY_H_
#define TINK_DAEAD_DETERMINISTIC_AEAD_FACTORY_H_

#include <memory>

#include "absl/base/macros.h"
#include "tink/deterministic_aead.h"
#include "tink/key_manager.h"
#include "tink/keyset_handle.h"
#include "tink/util/statusor.h"

namespace crypto {
namespace tink {

///////////////////////////////////////////////////////////////////////////////
// This class is deprecated. Call
// keyset_handle->GetPrimitive<DeterministicAead>() instead.
//
// Note that in order to for this change to be safe, the
// DeterministicAeadWrapper has to be registered in your binary before this
// call. This happens automatically if you call one of
// * DeterministicAeadConfig::Register()
// * TinkConfig::Register()
// NOLINTBEGIN(whitespace/line_length) (Formatted when commented in)
// TINK-PENDING-REMOVAL-IN-3.0.0-START
class ABSL_DEPRECATED(
    "Call getPrimitive<DeterministicAeadFactory>() on the keyset_handle after "
    "registering the DeterministicAeadWrapper instead.")
    DeterministicAeadFactory {
 public:
  // Returns an DeterministicAead-primitive that uses key material from
  // the keyset specified via 'keyset_handle'.
  static crypto::tink::util::StatusOr<std::unique_ptr<DeterministicAead>>
  GetPrimitive(const KeysetHandle& keyset_handle);

  // Returns an DeterministicAead-primitive that uses key material from
  // the keyset specified via 'keyset_handle' and is instantiated by the given
  // 'custom_key_manager' (instead of the key manager from the Registry).
  static crypto::tink::util::StatusOr<std::unique_ptr<DeterministicAead>>
  GetPrimitive(const KeysetHandle& keyset_handle,
               const KeyManager<DeterministicAead>* custom_key_manager);

 private:
  DeterministicAeadFactory() {}
};
// TINK-PENDING-REMOVAL-IN-3.0.0-END
// NOLINTEND(whitespace/line_length)

}  // namespace tink
}  // namespace crypto

#endif  // TINK_DAEAD_DETERMINISTIC_AEAD_FACTORY_H_
