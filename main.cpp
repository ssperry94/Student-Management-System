#include <handling.h>

//CURRENTLY: add final touches to project before final push to github

//get a few test case users and whatnot to each csv file

int main()
{
    char input;

    std::cout << "Welcome to the Student Manager Program!\n";
    while(input != 'q')
    {
        std::cout << "Are you a student or a teacher, or press 'q' to exit(S/T/Q)?\n";
        std::cin >> input;

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
