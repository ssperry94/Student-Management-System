#include <user_auth.h>

std::string smanEncrypt::key_path = "C:/Users/ssper/OneDrive/Desktop/CPP/Projects/Student Managerv2/key.key";

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

void smanEncrypt::generate_key(size_t key_size)
{
    std::ofstream keyfile;
    keyfile.open(key_path);
    if(!keyfile)
    {
        std::cout << "File couldn't be opened.\n";
        return;
    }
    std::vector <uint8_t> key(key_size);
    CryptoPP::NonblockingRng rng;
    rng.GenerateBlock(key.data(), key.size());

    for(uint8_t k : key)
    {
        keyfile << k;
    }
    keyfile.close();
}

//read all data from .key file, then pump into a string, then turn string into a vector
void smanEncrypt::retrieve_key(std::vector <uint8_t> &key)
{   
    std::string key_str; 
    CryptoPP::FileSource infile(key_path.c_str(), true, new CryptoPP::StringSink(key_str)); 

    for(int i = 0; i < key.size(); i++)
    {
        key[i] = key_str[i];
    }
    key.shrink_to_fit();
}

void smanEncrypt::generate_iv(std::vector <uint8_t> &iv)
{
    CryptoPP::NonblockingRng rand;
    rand.GenerateBlock(iv.data(), iv.size());
}