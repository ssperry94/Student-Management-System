// Copyright 2023 Google LLC
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
////////////////////////////////////////////////////////////////////////////////

#ifndef TINK_CONFIG_GLOBAL_REGISTRY_H_
#define TINK_CONFIG_GLOBAL_REGISTRY_H_

#include "tink/configuration.h"
#include "tink/key_gen_configuration.h"

namespace crypto {
namespace tink {

// Used to generate primitives and keys using the global crypto::tink::Registry.
const crypto::tink::Configuration& ConfigGlobalRegistry();
const crypto::tink::KeyGenConfiguration& KeyGenConfigGlobalRegistry();

}  // namespace tink
}  // namespace crypto

#endif  // TINK_CONFIG_GLOBAL_REGISTRY_H_
