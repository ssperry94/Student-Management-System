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
#ifndef TINK_JWT_INTERNAL_JWT_PUBLIC_KEY_SIGN_WRAPPER_H_
#define TINK_JWT_INTERNAL_JWT_PUBLIC_KEY_SIGN_WRAPPER_H_

#include <memory>

#include "tink/jwt/internal/jwt_public_key_sign_internal.h"
#include "tink/jwt/jwt_public_key_sign.h"
#include "tink/primitive_set.h"
#include "tink/primitive_wrapper.h"
#include "tink/util/statusor.h"

namespace crypto {
namespace tink {
namespace jwt_internal {

// Wraps a set of JwtPublicKeySign-instances that correspond to a keyset,
// and combines them into a single JwtPublicKeySign-primitive. It always
// uses the primary instance from the set in SignAndEncode. Only keys with RAW
// output prefix are supported.
class JwtPublicKeySignWrapper
    : public PrimitiveWrapper<JwtPublicKeySignInternal, JwtPublicKeySign> {
 public:
  util::StatusOr<std::unique_ptr<JwtPublicKeySign>> Wrap(
      std::unique_ptr<PrimitiveSet<JwtPublicKeySignInternal>> jwt_sign_set)
      const override;
};

}  // namespace jwt_internal
}  // namespace tink
}  // namespace crypto

#endif  // TINK_JWT_INTERNAL_JWT_PUBLIC_KEY_SIGN_WRAPPER_H_
