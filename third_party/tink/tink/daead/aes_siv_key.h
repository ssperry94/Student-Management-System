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

#ifndef TINK_DAEAD_AES_SIV_KEY_H_
#define TINK_DAEAD_AES_SIV_KEY_H_

#include <string>
#include <utility>

#include "absl/strings/string_view.h"
#include "absl/types/optional.h"
#include "tink/daead/aes_siv_parameters.h"
#include "tink/daead/deterministic_aead_key.h"
#include "tink/partial_key_access_token.h"
#include "tink/restricted_data.h"
#include "tink/util/statusor.h"

namespace crypto {
namespace tink {

// Represents a Deterministic AEAD that uses AES-SIV.
class AesSivKey : public DeterministicAeadKey {
 public:
  // Copyable and movable.
  AesSivKey(const AesSivKey& other) = default;
  AesSivKey& operator=(const AesSivKey& other) = default;
  AesSivKey(AesSivKey&& other) = default;
  AesSivKey& operator=(AesSivKey&& other) = default;

  // Creates a new AES-SIV key.  If the parameters specify a variant that uses
  // a prefix, then the id is used to compute this prefix.
  static util::StatusOr<AesSivKey> Create(const AesSivParameters& parameters,
                                          const RestrictedData& key_bytes,
                                          absl::optional<int> id_requirement,
                                          PartialKeyAccessToken token);

  // Returns the underlying AES-SIV key.
  const RestrictedData& GetKeyBytes(PartialKeyAccessToken token) const {
    return key_bytes_;
  }

  absl::string_view GetOutputPrefix() const override { return output_prefix_; }

  const AesSivParameters& GetParameters() const override { return parameters_; }

  absl::optional<int> GetIdRequirement() const override {
    return id_requirement_;
  }

  bool operator==(const Key& other) const override;

 private:
  AesSivKey(const AesSivParameters& parameters, const RestrictedData& key_bytes,
            absl::optional<int> id_requirement, std::string output_prefix)
      : parameters_(parameters),
        key_bytes_(key_bytes),
        id_requirement_(id_requirement),
        output_prefix_(std::move(output_prefix)) {}

  AesSivParameters parameters_;
  RestrictedData key_bytes_;
  absl::optional<int> id_requirement_;
  std::string output_prefix_;
};

}  // namespace tink
}  // namespace crypto

#endif  // TINK_DAEAD_AES_SIV_KEY_H_
