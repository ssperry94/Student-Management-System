#include <user_auth.h>


std::string smanEncrypt::encrypt(std::string &input, std::vector <uint8_t> key, std::vector <uint8_t> iv)
{
    std::string encrypted_text;

    auto aes = CryptoPP::AES::Encryption(key.data(), key.size());
    auto aes_cbc = CryptoPP::CBC_Mode_ExternalCipher::Encryption(aes, iv.data());

    CryptoPP::StringSource ss(
    input,
    true,
    new CryptoPP::StreamTransformationFilter(
        aes_cbc,
        new CryptoPP::Base64Encoder(
            new CryptoPP::StringSink(encrypted_text)
            )
        )
    );

    return encrypted_text;
}

std::string smanEncrypt::decrypt(std::string &input, std::vector <uint8_t> key, std::vector <uint8_t> iv)
{
    std::string decrypted_text;

    auto aes = CryptoPP::AES::Decryption(key.data(), key.size());
    auto aes_cbc = CryptoPP::CBC_Mode_ExternalCipher::Decryption(aes, iv.data());

    CryptoPP::StringSource ss(
    input,
    true,
    new CryptoPP::Base64Decoder(
        new CryptoPP::StreamTransformationFilter(
            aes_cbc,
            new CryptoPP::StringSink(decrypted_text)
            )
        )
    );

    return decrypted_text;
}