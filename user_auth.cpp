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

void smanEncrypt::generate_key(std::ofstream &keyfile, size_t size)
{
    std::vector <uint8_t> key(size);
    CryptoPP::NonblockingRng rng;
    rng.GenerateBlock(key.data(), key.size());

    for(uint8_t k : key)
    {
        keyfile << k;
    }
}

//read all data from .key file, then pump into a string, then turn string into a vector
std::vector <uint8_t> smanEncrypt::retrieve_key(std::string keyfile, std::vector <uint8_t> key)
{   
    std::string key_str; 
    std::vector <uint8_t> key_actual;
    CryptoPP::FileSource infile(keyfile.c_str(), true, new CryptoPP::StringSink(key_str)); 
    std::cout << key_str << '\n';

    std::cout << "After placing in vector...\n";
    for(char character : key_str)
    {
        key_actual.push_back(character);
    }

    return key_actual;

}