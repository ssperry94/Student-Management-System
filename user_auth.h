#include <managerclasses.h>
#include <aes.h>
#include <base64.h>
#include <osrng.h>
#include <modes.h>
#include <filters.h>
#include <files.h>

namespace smanEncrypt
{
    //filepath variables
    extern std::string key_path;
    //add filepaths for teacher and student login info

    //functions
    std::string encrypt(std::string &input, std::vector <uint8_t> key, std::vector <uint8_t> iv);
    std::string decrypt(std::string &input, std::vector <uint8_t> key, std::vector <uint8_t> iv);
    void generate_key(size_t key_size);
    void generate_iv(std::vector <uint8_t> &iv);
    void retrieve_key(std::vector <uint8_t> &key);
}