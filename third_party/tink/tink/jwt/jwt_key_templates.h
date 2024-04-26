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

#ifndef TINK_JWT_JWT_KEY_TEMPLATES_H_
#define TINK_JWT_JWT_KEY_TEMPLATES_H_

#include "proto/tink.pb.h"

namespace crypto {
namespace tink {

///////////////////////////////////////////////////////////////////////////////
// Pre-generated KeyTemplate for Jwt key types. One can use these templates
// to generate new KeysetHandle object with fresh keys. The templates with
// the "Raw" prefix generate tokens without a "kid" header.
//
// To generate a new keyset that contains a single JwtHmacKey, one can do:
//
//   auto status = JwtMacRegister();
//   if (!status.ok()) { /* fail with error */ }
//   auto handle_result =
//       KeysetHandle::GenerateNew(JwtHs256Template());
//   if (!handle_result.ok()) { /* fail with error */ }
//   auto keyset_handle = std::move(handle_result.value());
const google::crypto::tink::KeyTemplate& JwtHs256Template();
const google::crypto::tink::KeyTemplate& RawJwtHs256Template();
const google::crypto::tink::KeyTemplate& JwtHs384Template();
const google::crypto::tink::KeyTemplate& RawJwtHs384Template();
const google::crypto::tink::KeyTemplate& JwtHs512Template();
const google::crypto::tink::KeyTemplate& RawJwtHs512Template();

const google::crypto::tink::KeyTemplate& JwtEs256Template();
const google::crypto::tink::KeyTemplate& RawJwtEs256Template();
const google::crypto::tink::KeyTemplate& JwtEs384Template();
const google::crypto::tink::KeyTemplate& RawJwtEs384Template();
const google::crypto::tink::KeyTemplate& JwtEs512Template();
const google::crypto::tink::KeyTemplate& RawJwtEs512Template();

const google::crypto::tink::KeyTemplate& JwtRs256_2048_F4_Template();
const google::crypto::tink::KeyTemplate& RawJwtRs256_2048_F4_Template();
const google::crypto::tink::KeyTemplate& JwtRs256_3072_F4_Template();
const google::crypto::tink::KeyTemplate& RawJwtRs256_3072_F4_Template();
const google::crypto::tink::KeyTemplate& JwtRs384_3072_F4_Template();
const google::crypto::tink::KeyTemplate& RawJwtRs384_3072_F4_Template();
const google::crypto::tink::KeyTemplate& JwtRs512_4096_F4_Template();
const google::crypto::tink::KeyTemplate& RawJwtRs512_4096_F4_Template();

const google::crypto::tink::KeyTemplate& JwtPs256_2048_F4_Template();
const google::crypto::tink::KeyTemplate& RawJwtPs256_2048_F4_Template();
const google::crypto::tink::KeyTemplate& JwtPs256_3072_F4_Template();
const google::crypto::tink::KeyTemplate& RawJwtPs256_3072_F4_Template();
const google::crypto::tink::KeyTemplate& JwtPs384_3072_F4_Template();
const google::crypto::tink::KeyTemplate& RawJwtPs384_3072_F4_Template();
const google::crypto::tink::KeyTemplate& JwtPs512_4096_F4_Template();
const google::crypto::tink::KeyTemplate& RawJwtPs512_4096_F4_Template();

}  // namespace tink
}  // namespace crypto

#endif  // TINK_JWT_JWT_KEY_TEMPLATES_H_
