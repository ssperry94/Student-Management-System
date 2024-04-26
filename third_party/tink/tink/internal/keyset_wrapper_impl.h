// Copyright 2020 Google LLC
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

#ifndef TINK_INTERNAL_KEYSET_WRAPPER_IMPL_H_
#define TINK_INTERNAL_KEYSET_WRAPPER_IMPL_H_

#include <memory>
#include <string>
#include <utility>

#include "absl/container/flat_hash_map.h"
#include "absl/functional/any_invocable.h"
#include "tink/internal/key_info.h"
#include "tink/internal/keyset_wrapper.h"
#include "tink/primitive_set.h"
#include "tink/primitive_wrapper.h"
#include "tink/util/status.h"
#include "tink/util/statusor.h"
#include "tink/util/validation.h"
#include "proto/tink.pb.h"

namespace crypto {
namespace tink {
namespace internal {

template <typename P, typename Q>
class KeysetWrapperImpl : public KeysetWrapper<Q> {
 public:
  // We allow injection of a function creating the P primitive from KeyData for
  // testing -- later, this function will just be Registry::GetPrimitive().
  explicit KeysetWrapperImpl(
      const PrimitiveWrapper<P, Q>* transforming_wrapper,
      absl::AnyInvocable<crypto::tink::util::StatusOr<std::unique_ptr<P>>(
          const google::crypto::tink::KeyData& key_data) const>
          primitive_getter)
      : primitive_getter_(std::move(primitive_getter)),
        transforming_wrapper_(*transforming_wrapper) {}

  crypto::tink::util::StatusOr<std::unique_ptr<Q>> Wrap(
      const google::crypto::tink::Keyset& keyset,
      const absl::flat_hash_map<std::string, std::string>& annotations)
      const override {
    crypto::tink::util::Status status = ValidateKeyset(keyset);
    if (!status.ok()) return status;
    typename PrimitiveSet<P>::Builder primitives_builder;
    primitives_builder.AddAnnotations(annotations);
    for (const google::crypto::tink::Keyset::Key& key : keyset.key()) {
      if (key.status() != google::crypto::tink::KeyStatusType::ENABLED) {
        continue;
      }
      auto primitive = primitive_getter_(key.key_data());
      if (!primitive.ok()) return primitive.status();
      if (key.key_id() == keyset.primary_key_id()) {
        primitives_builder.AddPrimaryPrimitive(std::move(primitive.value()),
                                               KeyInfoFromKey(key));
      } else {
        primitives_builder.AddPrimitive(std::move(primitive.value()),
                                        KeyInfoFromKey(key));
      }
    }
    crypto::tink::util::StatusOr<PrimitiveSet<P>> primitives =
        std::move(primitives_builder).Build();
    if (!primitives.ok()) return primitives.status();
    return transforming_wrapper_.Wrap(
        absl::make_unique<PrimitiveSet<P>>(*std::move(primitives)));
  }

 private:
  absl::AnyInvocable<crypto::tink::util::StatusOr<std::unique_ptr<P>>(
      const google::crypto::tink::KeyData& key_data) const>
      primitive_getter_;
  const PrimitiveWrapper<P, Q>& transforming_wrapper_;
};

}  // namespace internal
}  // namespace tink
}  // namespace crypto

#endif  // TINK_INTERNAL_KEYSET_WRAPPER_IMPL_H_
