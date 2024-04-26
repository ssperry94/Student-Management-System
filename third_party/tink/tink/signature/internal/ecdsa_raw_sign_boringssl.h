// Copyright 2017 Google Inc.
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

#ifndef TINK_SIGNATURE_INTERNAL_ECDSA_RAW_SIGN_BORINGSSL_H_
#define TINK_SIGNATURE_INTERNAL_ECDSA_RAW_SIGN_BORINGSSL_H_

#include <memory>
#include <string>
#include <utility>

#include "absl/strings/string_view.h"
#include "openssl/ec.h"
#include "openssl/evp.h"
#include "tink/internal/fips_utils.h"
#include "tink/internal/ssl_unique_ptr.h"
#include "tink/public_key_sign.h"
#include "tink/subtle/common_enums.h"
#include "tink/subtle/subtle_util_boringssl.h"
#include "tink/util/statusor.h"

namespace crypto {
namespace tink {
namespace internal {

// ECDSA raw signing using Boring SSL, generating signatures in DER-encoding.
class EcdsaRawSignBoringSsl : public PublicKeySign {
 public:
  static crypto::tink::util::StatusOr<std::unique_ptr<EcdsaRawSignBoringSsl>>
  New(const crypto::tink::internal::EcKey& ec_key,
      subtle::EcdsaSignatureEncoding encoding);

  // Computes the signature for 'data'.
  crypto::tink::util::StatusOr<std::string> Sign(
      absl::string_view data) const override;

  static constexpr crypto::tink::internal::FipsCompatibility kFipsStatus =
      crypto::tink::internal::FipsCompatibility::kRequiresBoringCrypto;

 private:
  EcdsaRawSignBoringSsl(internal::SslUniquePtr<EC_KEY> key,
                        subtle::EcdsaSignatureEncoding encoding)
      : key_(std::move(key)), encoding_(encoding) {}

  internal::SslUniquePtr<EC_KEY> key_;
  subtle::EcdsaSignatureEncoding encoding_;
};

}  // namespace internal
}  // namespace tink
}  // namespace crypto

#endif  // TINK_SIGNATURE_INTERNAL_ECDSA_RAW_SIGN_BORINGSSL_H_
