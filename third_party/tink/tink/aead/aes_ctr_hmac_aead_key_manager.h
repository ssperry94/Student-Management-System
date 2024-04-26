// Copyright 2017 Google LLC
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
#ifndef TINK_AEAD_AES_CTR_HMAC_AEAD_KEY_MANAGER_H_
#define TINK_AEAD_AES_CTR_HMAC_AEAD_KEY_MANAGER_H_

#include <stdint.h>

#include <memory>
#include <string>

#include "absl/memory/memory.h"
#include "absl/strings/str_cat.h"
#include "tink/aead.h"
#include "tink/core/key_type_manager.h"
#include "tink/core/template_util.h"
#include "tink/internal/fips_utils.h"
#include "tink/util/constants.h"
#include "tink/util/status.h"
#include "tink/util/statusor.h"
#include "proto/aes_ctr_hmac_aead.pb.h"
#include "proto/tink.pb.h"

namespace crypto {
namespace tink {

class AesCtrHmacAeadKeyManager
    : public KeyTypeManager<google::crypto::tink::AesCtrHmacAeadKey,
                            google::crypto::tink::AesCtrHmacAeadKeyFormat,
                            List<Aead>> {
 public:
  class AeadFactory : public PrimitiveFactory<Aead> {
    crypto::tink::util::StatusOr<std::unique_ptr<Aead>> Create(
        const google::crypto::tink::AesCtrHmacAeadKey& key) const override;
  };

  AesCtrHmacAeadKeyManager()
      : KeyTypeManager(absl::make_unique<AeadFactory>()) {}

  uint32_t get_version() const override { return 0; }

  google::crypto::tink::KeyData::KeyMaterialType key_material_type()
      const override {
    return google::crypto::tink::KeyData::SYMMETRIC;
  }

  const std::string& get_key_type() const override { return key_type_; }

  crypto::tink::util::Status ValidateKey(
      const google::crypto::tink::AesCtrHmacAeadKey& key) const override;
  crypto::tink::util::Status ValidateKeyFormat(
      const google::crypto::tink::AesCtrHmacAeadKeyFormat& key) const override;

  crypto::tink::util::StatusOr<google::crypto::tink::AesCtrHmacAeadKey>
  CreateKey(const google::crypto::tink::AesCtrHmacAeadKeyFormat& key_format)
      const override;

  crypto::tink::util::StatusOr<google::crypto::tink::AesCtrHmacAeadKey>
  DeriveKey(const google::crypto::tink::AesCtrHmacAeadKeyFormat& key_format,
            InputStream* input_stream) const override;

  internal::FipsCompatibility FipsStatus() const override {
    return internal::FipsCompatibility::kRequiresBoringCrypto;
  }

 private:
  const std::string key_type_ =
      absl::StrCat(kTypeGoogleapisCom,
                   google::crypto::tink::AesCtrHmacAeadKey().GetTypeName());
};

}  // namespace tink
}  // namespace crypto

#endif  // TINK_AEAD_AES_CTR_HMAC_AEAD_KEY_MANAGER_H_
