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
    extern std::string teacher_path;
    extern std::string student_path;


    //parent class containing shared attributes
    class UserCommon
    {
        protected:
            std::string filepath, username, password;
            bool is_teacher;
        
        public:
            UserCommon(bool is_teacher, std::string username, std::string password);
    };
    //class for user registration

    class UserRegistrator:public UserCommon 
    {
        public:
            UserRegistrator(bool is_teacher, std::string username, std::string password);

            void add_account(std::vector <uint8_t> key);

            void write_iv(std::fstream &outfile, std::vector <uint8_t> &iv);
            void reset(); //resets files for testing purposes (may repurpose later)
    };

    //class for logging in
    class LoggingIn:public UserCommon
    {
        public:
            LoggingIn(bool is_teacher, std::string username, std::string password);
            void retreive_account(std::string &entered_username, std::string &entered_password, std::vector <uint8_t> &iv, std::streampos &current_pos);
            void retrieve_iv(std::ifstream &infile, std::vector <uint8_t> &iv);
    };

    //functions
    std::string encrypt(std::string &input, std::vector <uint8_t> key, std::vector <uint8_t> iv);
    std::string decrypt(std::string &input, std::vector <uint8_t> key, std::vector <uint8_t> iv);
    void generate_key(size_t key_size);
    void generate_iv(std::vector <uint8_t> &iv);
    void retrieve_key(std::vector <uint8_t> &key);

}

#endif