#include <handling.h>

//CURRENTLY: Come up with way to structure student registration/login system

//to add_account() - add various if statements for getting the student id, then encrypting that along with all other user info
//something similar for retrieve accounts, may need to make an overloaded function

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
    smanEncrypt::UserRegistrator registrator(true, "teacher", "123");
    smanEncrypt::UserRegistrator registrator2(true, "teacher1", "321");
    std::string username, password;
    registrator.reset();

    static constexpr size_t AES_KEY_SIZE = 256 / 8;
    std::vector<uint8_t> key(AES_KEY_SIZE);

    smanEncrypt::retrieve_key(key);

    registrator.add_account(key);
    registrator2.add_account(key);
}