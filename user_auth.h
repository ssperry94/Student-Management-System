#include <managerclasses.h>
#include <aes.h>
#include <base64.h>
#include <osrng.h>
#include <modes.h>
#include <filters.h>
#include <files.h>

namespace smanEncrypt
{
    std::string encrypt(std::string &input, std::vector <uint8_t> key, std::vector <uint8_t> iv);
    std::string decrypt(std::string &input, std::vector <uint8_t> key, std::vector <uint8_t> iv);
    void generate_key(std::ofstream &keyfile, size_t size);
    std::vector <uint8_t> retrieve_key(std::string keyfile, std::vector <uint8_t> key);
}