// Copyright 2023 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef TINK_SIGNATURE_RSA_SSA_PKCS1_PUBLIC_KEY_H_
#define TINK_SIGNATURE_RSA_SSA_PKCS1_PUBLIC_KEY_H_

#include <string>

#include "absl/strings/string_view.h"
#include "absl/types/optional.h"
#include "tink/big_integer.h"
#include "tink/key.h"
#include "tink/partial_key_access_token.h"
#include "tink/signature/rsa_ssa_pkcs1_parameters.h"
#include "tink/signature/signature_public_key.h"
#include "tink/util/statusor.h"

namespace crypto {
namespace tink {

// Representation of the public key for the RsaSsaPkcs1 digital
// signature scheme.
class RsaSsaPkcs1PublicKey : public SignaturePublicKey {
 public:
  // Copyable and movable.
  RsaSsaPkcs1PublicKey(const RsaSsaPkcs1PublicKey& other) = default;
  RsaSsaPkcs1PublicKey& operator=(const RsaSsaPkcs1PublicKey& other) = default;
  RsaSsaPkcs1PublicKey(RsaSsaPkcs1PublicKey&& other) = default;
  RsaSsaPkcs1PublicKey& operator=(RsaSsaPkcs1PublicKey&& other) = default;

  // Creates a new RsaSsaPkcs1 public key from `modulus`. If
  // `parameters` specify a variant that uses a prefix, then `id_requirement` is
  // used to compute this prefix.
  static util::StatusOr<RsaSsaPkcs1PublicKey> Create(
      const RsaSsaPkcs1Parameters& parameters, const BigInteger& modulus,
      absl::optional<int> id_requirement, PartialKeyAccessToken token);

  const BigInteger& GetModulus(PartialKeyAccessToken token) const {
    return modulus_;
  }

  absl::string_view GetOutputPrefix() const override { return output_prefix_; }

  const RsaSsaPkcs1Parameters& GetParameters() const override {
    return parameters_;
  }

  absl::optional<int> GetIdRequirement() const override {
    return id_requirement_;
  }

  bool operator==(const Key& other) const override;

 private:
  explicit RsaSsaPkcs1PublicKey(const RsaSsaPkcs1Parameters& parameters,
                                const BigInteger& modulus,
                                absl::optional<int> id_requirement,
                                absl::string_view output_prefix)
      : parameters_(parameters),
        modulus_(modulus),
        id_requirement_(id_requirement),
        output_prefix_(output_prefix) {}

  RsaSsaPkcs1Parameters parameters_;
  BigInteger modulus_;
  absl::optional<int> id_requirement_;
  std::string output_prefix_;
};

}  // namespace tink
}  // namespace crypto

#endif  // TINK_SIGNATURE_RSA_SSA_PKCS1_PUBLIC_KEY_H_
