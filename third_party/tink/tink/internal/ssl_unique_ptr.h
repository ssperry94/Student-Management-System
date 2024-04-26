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
#ifndef TINK_INTERNAL_SSL_UNIQUE_PTR_H_
#define TINK_INTERNAL_SSL_UNIQUE_PTR_H_

#include <memory>

// Every header in BoringSSL includes base.h, which in turn defines
// OPENSSL_IS_BORINGSSL. So we include this common header here to "force" the
// definition of OPENSSL_IS_BORINGSSL in case BoringSSL is used.
#include "openssl/crypto.h"

#ifndef OPENSSL_IS_BORINGSSL
#include "openssl/bn.h"
#include "openssl/cmac.h"
#include "openssl/ec.h"
#include "openssl/evp.h"
#include "openssl/hmac.h"
#include "openssl/rsa.h"
#endif

namespace crypto {
namespace tink {
namespace internal {

#ifdef OPENSSL_IS_BORINGSSL

// In this case, simply use BoringSSL's UniquePtr.
template <typename T>
using SslUniquePtr = ::bssl::UniquePtr<T>;

#else

// We define SslUniquePtr similarly to how bssl::UniquePtr<T> is defined,
// i.e., as a unique_ptr with custom deleter for each type T. The difference
// w.r.t. the BoringSSL equivalent is that we have to define each deleter here
// explicitly, while bssl::UniquePtr allows for forward declaration and
// later specialization when including specific headers. This is possible in
// BoringSSL because each module's header defines the appropriate deleter with
// BORINGSSL_MAKE_DELETER, which is not the case for OpenSSL.

template <typename T>
struct Deleter {
  void operator()(T* ptr);
};

// Here are all the custom deleters.
template <>
struct Deleter<BIO> {
  void operator()(BIO* ptr) { BIO_free(ptr); }
};
template <>
struct Deleter<EVP_CIPHER_CTX> {
  void operator()(EVP_CIPHER_CTX* ptr) { EVP_CIPHER_CTX_free(ptr); }
};
template <>
struct Deleter<BIGNUM> {
  void operator()(BIGNUM* ptr) { BN_free(ptr); }
};
template <>
struct Deleter<BN_CTX> {
  void operator()(BN_CTX* ptr) { BN_CTX_free(ptr); }
};
template <>
struct Deleter<RSA> {
  void operator()(RSA* ptr) { RSA_free(ptr); }
};
template <>
struct Deleter<EC_POINT> {
  void operator()(EC_POINT* ptr) { EC_POINT_free(ptr); }
};
template <>
struct Deleter<EC_GROUP> {
  void operator()(EC_GROUP* ptr) { EC_GROUP_free(ptr); }
};
template <>
struct Deleter<EC_KEY> {
  void operator()(EC_KEY* ptr) { EC_KEY_free(ptr); }
};
template <>
struct Deleter<EVP_PKEY> {
  void operator()(EVP_PKEY* ptr) { EVP_PKEY_free(ptr); }
};
template <>
struct Deleter<EVP_PKEY_CTX> {
  void operator()(EVP_PKEY_CTX* ptr) { EVP_PKEY_CTX_free(ptr); }
};
template <>
struct Deleter<ECDSA_SIG> {
  void operator()(ECDSA_SIG* ptr) { ECDSA_SIG_free(ptr); }
};
template <>
struct Deleter<CMAC_CTX> {
  void operator()(CMAC_CTX* ptr) { CMAC_CTX_free(ptr); }
};
template <>
struct Deleter<EVP_MD_CTX> {
  void operator()(EVP_MD_CTX* ptr) { EVP_MD_CTX_free(ptr); }
};
template <>
struct Deleter<HMAC_CTX> {
  void operator()(HMAC_CTX* ptr) { HMAC_CTX_free(ptr); }
};

template <typename T>
using SslUniquePtr = std::unique_ptr<T, Deleter<T> >;

#endif  // OPENSSL_IS_BORINGSSL

}  // namespace internal
}  // namespace tink
}  // namespace crypto

#endif  // TINK_INTERNAL_SSL_UNIQUE_PTR_H_
