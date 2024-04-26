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

#ifndef TINK_JWT_VERIFIED_JWT_H_
#define TINK_JWT_VERIFIED_JWT_H_

#include <string>
#include <vector>

#include "google/protobuf/struct.pb.h"
#include "absl/strings/string_view.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "tink/jwt/raw_jwt.h"
#include "tink/util/status.h"
#include "tink/util/statusor.h"

namespace crypto {
namespace tink {

namespace jwt_internal {

// For friend declaration
class JwtMacImpl;
class JwtPublicKeyVerifyImpl;

}

///////////////////////////////////////////////////////////////////////////////
// A decoded and verified JSON Web Token (JWT).
//
// A new instance of this class is returned as the result of a sucessfully
// verification of a MACed or signed compact JWT.
//
// It gives read-only access all payload claims and a subset of the headers. It
// does not contain any headers that depend on the key, such as "alg" or "kid".
// These headers are checked when the signature is verified and should not be
// read by the user. This ensures that the key can be changed without any
// changes to the user code.
class VerifiedJwt {
 public:
  // VerifiedJwt objects are copiable and implicitly movable.
  VerifiedJwt(const VerifiedJwt&) = default;
  VerifiedJwt& operator=(const VerifiedJwt&) = default;

  bool HasTypeHeader() const;
  util::StatusOr<std::string> GetTypeHeader() const;
  bool HasIssuer() const;
  util::StatusOr<std::string> GetIssuer() const;
  bool HasSubject() const;
  util::StatusOr<std::string> GetSubject() const;
  bool HasAudiences() const;
  util::StatusOr<std::vector<std::string>> GetAudiences() const;
  bool HasJwtId() const;
  util::StatusOr<std::string> GetJwtId() const;
  bool HasExpiration() const;
  util::StatusOr<absl::Time> GetExpiration() const;
  bool HasNotBefore() const;
  util::StatusOr<absl::Time> GetNotBefore() const;
  bool HasIssuedAt() const;
  util::StatusOr<absl::Time> GetIssuedAt() const;

  bool IsNullClaim(absl::string_view name) const;
  bool HasBooleanClaim(absl::string_view name) const;
  util::StatusOr<bool> GetBooleanClaim(absl::string_view name) const;
  bool HasStringClaim(absl::string_view name) const;
  util::StatusOr<std::string> GetStringClaim(absl::string_view name) const;
  bool HasNumberClaim(absl::string_view name) const;
  util::StatusOr<double> GetNumberClaim(absl::string_view name) const;
  bool HasJsonObjectClaim(absl::string_view name) const;
  util::StatusOr<std::string> GetJsonObjectClaim(absl::string_view name) const;
  bool HasJsonArrayClaim(absl::string_view name) const;
  util::StatusOr<std::string> GetJsonArrayClaim(absl::string_view name) const;
  std::vector<std::string> CustomClaimNames() const;

  util::StatusOr<std::string> GetJsonPayload();

 private:
  VerifiedJwt();
  explicit VerifiedJwt(const RawJwt& raw_jwt);
  friend class jwt_internal::JwtMacImpl;
  friend class jwt_internal::JwtPublicKeyVerifyImpl;
  RawJwt raw_jwt_;
};

}  // namespace tink
}  // namespace crypto

#endif  // TINK_JWT_VERIFIED_JWT_H_
