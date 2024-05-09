#include <handling.h>

//make user authentication in cpp
//write real documentation on how to use, functions, etc
//add a way to exit or erase if a mistake was made
//add a way to edit information

//CURRENTLY: Structure all user_auth functions and integrate into main.cpp


void testCryptoPP();

int main()
{
    testCryptoPP();
    std::system("pause");
    char input;

    std::cout << "Welcome to the Student Manager Program!\n";
    while(input != 'q')
    {
        std::cout << "Are you a student or a teacher, or press 'q' to exit(S/T/Q)?\n";
        std::cin >> input;

        //clears input buffer, need to investigate to make sure that this is the best way to deal with it
        std::cin.sync();

        if(input == 'S' || input == 's')
        {
            handle_student_options();
            break;
        }
        
        else if(input == 'T' || input == 't')
        {
            handle_teacher_options();
            break;
        }
        else if(input == 'Q' || input == 'q')
        {
            break;
        }
        else
        {
            std::cout << "Please enter either a 'S' for student, 'T' for teacher, or 'q' to quit. Your response is not caps sensitive.\n\n";
        }
    }
    std::cout << "Goodbye!\n";
    return 0;
}


void testCryptoPP()
{
    smanEncrypt::UserRegistrator registrator(false, "student", "123");
    std::string username, password;
    registrator.reset();

    static constexpr size_t AES_KEY_SIZE = 256 / 8;
    // std::string message = "Hello world.";
    std::vector<uint8_t> key(AES_KEY_SIZE);


    smanEncrypt::generate_key(AES_KEY_SIZE);
    std::vector<uint8_t> iv(CryptoPP::AES::BLOCKSIZE);

    smanEncrypt::retrieve_key(key);

    registrator.add_account(key);

    smanEncrypt::retreive_account(smanEncrypt::student_path, username, password, iv);

    std::cout << smanEncrypt::decrypt(username, key, iv) << '\n' << smanEncrypt::decrypt(password, key, iv) << '\n';
}