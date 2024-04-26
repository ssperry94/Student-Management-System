// Copyright 2019 Google LLC
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

#include "tink/streamingaead/decrypting_random_access_stream.h"

#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

#include "absl/memory/memory.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "absl/synchronization/mutex.h"
#include "tink/primitive_set.h"
#include "tink/random_access_stream.h"
#include "tink/streaming_aead.h"
#include "tink/streamingaead/shared_random_access_stream.h"
#include "tink/util/buffer.h"
#include "tink/util/errors.h"
#include "tink/util/status.h"
#include "tink/util/statusor.h"

namespace crypto {
namespace tink {
namespace streamingaead {

using crypto::tink::PrimitiveSet;
using crypto::tink::StreamingAead;
using util::Status;
using util::StatusOr;

using StreamingAeadEntry = PrimitiveSet<StreamingAead>::Entry<StreamingAead>;

// static
StatusOr<std::unique_ptr<RandomAccessStream>> DecryptingRandomAccessStream::New(
    std::shared_ptr<PrimitiveSet<StreamingAead>> primitives,
    std::unique_ptr<crypto::tink::RandomAccessStream> ciphertext_source,
    absl::string_view associated_data) {
  if (primitives == nullptr) {
    return Status(absl::StatusCode::kInvalidArgument,
                  "primitives must be non-null.");
  }
  if (ciphertext_source == nullptr) {
    return Status(absl::StatusCode::kInvalidArgument,
                  "ciphertext_source must be non-null.");
  }
  return {absl::WrapUnique(new DecryptingRandomAccessStream(
      primitives, std::move(ciphertext_source), associated_data))};
}

util::Status DecryptingRandomAccessStream::PRead(
    int64_t position, int count, crypto::tink::util::Buffer* dest_buffer) {
  if (dest_buffer == nullptr) {
    return util::Status(absl::StatusCode::kInvalidArgument,
                        "dest_buffer must be non-null");
  }
  if (count < 0) {
    return util::Status(absl::StatusCode::kInvalidArgument,
                        "count cannot be negative");
  }
  if (count > dest_buffer->allocated_size()) {
    return util::Status(absl::StatusCode::kInvalidArgument, "buffer too small");
  }
  if (position < 0) {
    return util::Status(absl::StatusCode::kInvalidArgument,
                        "position cannot be negative");
  }
  crypto::tink::util::StatusOr<crypto::tink::RandomAccessStream*>
      matched_stream = GetMatchedStream();
  if (!matched_stream.ok()) {
    return matched_stream.status();
  }
  return (*matched_stream)->PRead(position, count, dest_buffer);
}

crypto::tink::util::StatusOr<crypto::tink::RandomAccessStream*>
DecryptingRandomAccessStream::GetMatchedStream() const {
  {
    absl::ReaderMutexLock lock(&matching_mutex_);
    if (attempted_matching_) {
      if (matching_stream_ != nullptr) {
        return matching_stream_.get();
      }
      return Status(absl::StatusCode::kInvalidArgument,
                    "Did not find a decrypter matching the ciphertext stream.");
    }
  }
  // Matching has not been attempted yet, so try it now.
  absl::MutexLock lock(&matching_mutex_);

  // Re-check that matching hasn't been attempted in the meantime.
  if (attempted_matching_) {
    if (matching_stream_ != nullptr) {
      return matching_stream_.get();
    }
    return Status(absl::StatusCode::kInvalidArgument,
                  "Did not find a decrypter matching the ciphertext stream.");
  }

  attempted_matching_ = true;
  std::vector<StreamingAeadEntry*> all_primitives = primitives_->get_all();
  util::StatusOr<std::unique_ptr<crypto::tink::util::Buffer>> buffer =
      crypto::tink::util::Buffer::New(1);
  if (!buffer.ok()) {
    return buffer.status();
  }
  for (const StreamingAeadEntry* entry : all_primitives) {
    StreamingAead& streaming_aead = entry->get_primitive();
    auto shared_ct =
        absl::make_unique<SharedRandomAccessStream>(ciphertext_source_.get());
    auto decrypting_stream_result =
        streaming_aead.NewDecryptingRandomAccessStream(std::move(shared_ct),
                                                       associated_data_);
    if (decrypting_stream_result.ok()) {
      Status read_result =
          decrypting_stream_result.value()->PRead(0, 1, buffer->get());
      if (read_result.ok() || absl::IsOutOfRange(read_result)) {
        // Found a match.
        matching_stream_ = std::move(decrypting_stream_result.value());
        return matching_stream_.get();
      }
    }
    // Not a match, try the next primitive.
  }
  return Status(absl::StatusCode::kInvalidArgument,
                "Could not find a decrypter matching the ciphertext stream.");
}

StatusOr<int64_t> DecryptingRandomAccessStream::size() {
  crypto::tink::util::StatusOr<crypto::tink::RandomAccessStream*>
      matched_stream = GetMatchedStream();
  if (!matched_stream.ok()) {
    return matched_stream.status();
  }
  return (*matched_stream)->size();
}

}  // namespace streamingaead
}  // namespace tink
}  // namespace crypto
