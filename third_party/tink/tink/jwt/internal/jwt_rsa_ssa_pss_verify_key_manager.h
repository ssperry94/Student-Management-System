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
#ifndef TINK_JWT_INTERNAL_JWT_RSA_SSA_PSS_VERIFY_KEY_MANAGER_H_
#define TINK_JWT_INTERNAL_JWT_RSA_SSA_PSS_VERIFY_KEY_MANAGER_H_

#include <memory>
#include <string>

#include "absl/memory/memory.h"
#include "tink/core/key_type_manager.h"
#include "tink/jwt/internal/jwt_public_key_verify_impl.h"
#include "tink/jwt/internal/jwt_public_key_verify_internal.h"
#include "tink/jwt/internal/raw_jwt_rsa_ssa_pss_verify_key_manager.h"
#include "tink/util/status.h"
#include "tink/util/statusor.h"
#include "proto/jwt_rsa_ssa_pss.pb.h"

namespace crypto {
namespace tink {
namespace jwt_internal {

class JwtRsaSsaPssVerifyKeyManager
    : public KeyTypeManager<google::crypto::tink::JwtRsaSsaPssPublicKey, void,
                            List<JwtPublicKeyVerifyInternal>> {
 public:
  class PublicKeyVerifyFactory
      : public PrimitiveFactory<JwtPublicKeyVerifyInternal> {
    crypto::tink::util::StatusOr<std::unique_ptr<JwtPublicKeyVerifyInternal>>
    Create(const google::crypto::tink::JwtRsaSsaPssPublicKey&
               jwt_rsa_ssa_pss_public_key) const override;

   private:
    const RawJwtRsaSsaPssVerifyKeyManager raw_key_manager_;
  };

  JwtRsaSsaPssVerifyKeyManager()
      : KeyTypeManager(absl::make_unique<PublicKeyVerifyFactory>()) {}

  uint32_t get_version() const override;

  google::crypto::tink::KeyData::KeyMaterialType key_material_type()
      const override;

  const std::string& get_key_type() const override;

  crypto::tink::util::Status ValidateKey(
      const google::crypto::tink::JwtRsaSsaPssPublicKey& key) const override;

  internal::FipsCompatibility FipsStatus() const override {
    return internal::FipsCompatibility::kRequiresBoringCrypto;
  }

 private:
  static crypto::tink::util::StatusOr<std::string> AlgorithmName(
      const google::crypto::tink::JwtRsaSsaPssAlgorithm& algorithm);
  const RawJwtRsaSsaPssVerifyKeyManager raw_key_manager_;
  friend class JwtRsaSsaPssSignKeyManager;
};

}  // namespace jwt_internal
}  // namespace tink
}  // namespace crypto

#endif  // TINK_JWT_INTERNAL_JWT_RSA_SSA_PSS_VERIFY_KEY_MANAGER_H_
