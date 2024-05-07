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
            const std::string teacher_path = "C:/Users/ssper/OneDrive/Desktop/CPP/Projects/Student Managerv2/teach_login.csv";
            const std::string student_path = "C:/Users/ssper/OneDrive/Desktop/CPP/Projects/Student Managerv2/student_login.csv";
            bool is_teacher;
        public:
            UserRegistrator(bool is_teacher);

            void register_teacher();

            void register_student();
    };
    //functions
    std::string encrypt(std::string &input, std::vector <uint8_t> key, std::vector <uint8_t> iv);
    std::string decrypt(std::string &input, std::vector <uint8_t> key, std::vector <uint8_t> iv);
    void generate_key(size_t key_size);
    void generate_iv(std::vector <uint8_t> &iv);
    void retrieve_key(std::vector <uint8_t> &key);
}