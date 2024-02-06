#include <iostream>
#include <C:\Users\ssper\OneDrive\Desktop\CPP\Projects\Student Managerv2\managerclasses.h>

//maybe make a python script to verify user info? 
//should see about maybe making a GUI at some point
//write real documentation on how to use, functions, etc

//CURRENTLY: redoing main.cpp

//code with teacher options
void teacher();

//code with student options
void student();

int main()
{
    char input;

    std::cout << "Welcome to the Student Manager Program!\n";
    while(input != 'q')
    {
        std::cout << "Are you a student or a teacher (S/T)?\n";
        std::cin >> input;

        if(input == 'S' || input == 's')
        {
            student();
            
            //delete me
            std::cout << "Running student options...\n";
            break;
        }
        else if(input == 'T' || input == 't')
        {
            teacher();
            //delete me
            std::cout << "Running teacher options...\n";
            break;
        }
        else if(input == 'Q' || input == 'q')
        {
            break;
        }
        else
        {
            std::cout << "Please enter either a 'S' for student, 'T' for teacher, or 'q' to quit. Your response is not caps sensitive.\n";
        }
    }
    std::cout << "Goodbye!\n";
    return 0;
}

void teacher()
{
    //some code
}

void student()
{
    //some code
}