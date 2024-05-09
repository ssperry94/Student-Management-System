#ifndef USER_AUTH_H
#define USER_AUTH_H 


//contains functions and classes related to encrypted/decrypting and verifying user data

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

    //class for user registration

    class UserRegistrator 
    {
        private:
            std::string filepath;
            bool is_teacher;
            std::string username, password;

            void write_iv(std::fstream &outfile, std::vector <uint8_t> &iv);

        public:
            UserRegistrator(bool is_teacher, std::string username, std::string password);

            void add_account(std::vector <uint8_t> key);

            void retrieve_iv(std::ifstream &infile, std::vector <uint8_t> &iv);

            void retreive_account(std::string &username, std::string &password, std::vector <uint8_t> &iv);

            void reset(); //resets files for testing purposes (may repurpose later)
    };

    //functions
    std::string encrypt(std::string &input, std::vector <uint8_t> key, std::vector <uint8_t> iv);
    std::string decrypt(std::string &input, std::vector <uint8_t> key, std::vector <uint8_t> iv);
    void generate_key(size_t key_size);
    void generate_iv(std::vector <uint8_t> &iv);
    void retrieve_key(std::vector <uint8_t> &key);
}

#endif