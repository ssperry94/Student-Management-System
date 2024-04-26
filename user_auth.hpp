


    // 1. Get a handle to the key material.
    KeysetHandle keyset_handle = ...;

    // 2. Get the primitive.
    auto aead_result= keyset_handle.GetPrimitive<Aead>();
    if (!aead_result.ok()) return aead_result.status();
    auto aead = std::move(aead_result.ValueOrDie());

    // 3. Use the primitive.
    auto ciphertext_result = aead.Encrypt(plaintext, aad);
    if (!ciphertext_result.ok()) return ciphertext_result.status();
    auto ciphertext = std::move(ciphertext_result.ValueOrDie());