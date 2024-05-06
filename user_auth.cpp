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
void smanEncrypt::retrieve_key(std::string keyfile, std::vector <uint8_t> &key)
{   
    std::string key_str; 
    CryptoPP::FileSource infile(keyfile.c_str(), true, new CryptoPP::StringSink(key_str)); 

    for(auto i = 0; i < key.size(); i++)
    {
        std::cout << key_str[i] << '\n';
        key[i] = key_str[i];
    }
    key.shrink_to_fit();
    std::cout << "Size of vector: " << key.size() << '\n';

    std::cout << "Everyting in array: \n";
    for(int i = 0; i < key.size(); i++)
    {
        std::cout << key[i] << '\n';
    }
}