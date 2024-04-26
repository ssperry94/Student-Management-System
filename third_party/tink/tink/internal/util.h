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
#ifndef TINK_INTERNAL_UTIL_H_
#define TINK_INTERNAL_UTIL_H_

#include "absl/base/attributes.h"
#include "absl/strings/string_view.h"

namespace crypto {
namespace tink {
namespace internal {

// Return an empty string if str.data() is nullptr; otherwise return str.
absl::string_view EnsureStringNonNull(absl::string_view str);

// Returns true if `first` overlaps with `second`.
bool BuffersOverlap(absl::string_view first, absl::string_view second);

// Returns true if `first` fully overlaps with `second`.
bool BuffersAreIdentical(absl::string_view first, absl::string_view second);

// Returns true if `input` only contains printable ASCII characters (whitespace
// is not allowed).
bool IsPrintableAscii(absl::string_view input);

// Returns true if built on Windows; false otherwise.
inline bool IsWindows() {
#if defined(_WIN32)
  return true;
#else
  return false;
#endif
}

// Wraps Abseil's LOG(FATAL) macro and sets the [noreturn] attribute, which is
// useful for avoiding false positive [-Werror=return-type] compiler errors.
ABSL_ATTRIBUTE_NORETURN void LogFatal(absl::string_view msg);

}  // namespace internal
}  // namespace tink
}  // namespace crypto

#endif  // TINK_INTERNAL_UTIL_H_
