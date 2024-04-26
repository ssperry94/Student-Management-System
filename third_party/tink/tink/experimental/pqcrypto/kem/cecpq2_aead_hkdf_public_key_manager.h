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
#ifndef TINK_EXPERIMENTAL_PQCRYPTO_KEM_CECPQ2_AEAD_HKDF_PUBLIC_KEY_MANAGER_H_
#define TINK_EXPERIMENTAL_PQCRYPTO_KEM_CECPQ2_AEAD_HKDF_PUBLIC_KEY_MANAGER_H_

#include <memory>
#include <string>

#include "absl/memory/memory.h"
#include "absl/strings/str_cat.h"
#include "tink/core/key_type_manager.h"
#include "tink/experimental/pqcrypto/kem/cecpq2_aead_hkdf_dem_helper.h"
#include "tink/experimental/pqcrypto/kem/subtle/cecpq2_aead_hkdf_hybrid_encrypt.h"
#include "tink/hybrid_encrypt.h"
#include "tink/util/enums.h"
#include "tink/util/errors.h"
#include "tink/util/protobuf_helper.h"
#include "tink/util/status.h"
#include "tink/util/statusor.h"
#include "proto/experimental/pqcrypto/cecpq2_aead_hkdf.pb.h"
#include "proto/tink.pb.h"

namespace crypto {
namespace tink {

class Cecpq2AeadHkdfPublicKeyManager
    : public KeyTypeManager<google::crypto::tink::Cecpq2AeadHkdfPublicKey, void,
                            List<HybridEncrypt>> {
 public:
  class HybridEncryptFactory : public PrimitiveFactory<HybridEncrypt> {
    crypto::tink::util::StatusOr<std::unique_ptr<HybridEncrypt>> Create(
        const google::crypto::tink::Cecpq2AeadHkdfPublicKey& cecpq2_public_key)
        const override {
      return Cecpq2AeadHkdfHybridEncrypt::New(cecpq2_public_key);
    }
  };

  Cecpq2AeadHkdfPublicKeyManager()
      : KeyTypeManager(absl::make_unique<HybridEncryptFactory>()) {}

  uint32_t get_version() const override { return 0; }

  google::crypto::tink::KeyData::KeyMaterialType key_material_type()
      const override {
    return google::crypto::tink::KeyData::ASYMMETRIC_PUBLIC;
  }

  const std::string& get_key_type() const override { return key_type_; }

  crypto::tink::util::Status ValidateKey(
      const google::crypto::tink::Cecpq2AeadHkdfPublicKey& key) const override;

  crypto::tink::util::Status ValidateParams(
      const google::crypto::tink::Cecpq2AeadHkdfParams& params) const;

 private:
  const std::string key_type_ = absl::StrCat(
      "type.googleapis.com/",
      google::crypto::tink::Cecpq2AeadHkdfPublicKey().GetTypeName());
};

}  // namespace tink
}  // namespace crypto

#endif  // TINK_EXPERIMENTAL_PQCRYPTO_KEM_CECPQ2_AEAD_HKDF_PUBLIC_KEY_MANAGER_H_
