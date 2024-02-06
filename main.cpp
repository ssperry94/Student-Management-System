#include <iostream>
#include <iomanip>
#include <C:\Users\ssper\OneDrive\Desktop\CPP\Projects\Student Managerv2\managerclasses.h>

//maybe make a python script to verify user info? 
//should see about maybe making a GUI at some point
//write real documentation on how to use, functions, etc
//fix formatting to make it look better


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

        //clears input buffer, need to investigate to make sure that this is the best way to deal with it
        std::cin.sync();

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
    Student student1;
    if(!student1.get_authorize_code())
    {
        return;
    }

    std::string idnum = student1.get_idnum();
    std::cout << "Greetings student!\n";
    while(true)
    {
        int user_response;
        std::cout << "Please select the action you wish to take:\n";
        std::cout << "1. View your information.\n";
        std::cout << "2. View your schedule.\n";
        std::cout << "3. View your grades.\n";
        std::cout << "4. Quit.\n";
        std::cin >> user_response;
        std::cin.sync(); 

        switch(user_response)
        {
            case 1:
            {
                std::vector <std::string> student_info = student1.get_student("students.csv", idnum);
                std::cout << std::setw(50) << "ID Number: " << student_info[0] << '\n';
                std::cout << std::setw(50) << "First Name: " << student_info[1] << '\n';
                std::cout << std::setw(50) << "Last Name: " << student_info[2] << '\n';
                std::cout << std::setw(50) << "Date of Birth: " << student_info[3] << "\n\n";
                break;
            }

            case 2:
            {
                std::vector <std::string> info = student1.get_student("schedule.csv", idnum);
                if(info[0] == "1")
                {
                    std::cout << "ERROR, no schedule found for " << idnum << '\n';
                }

                else
                {
                    std::cout << "Student ID number: " << info[0] << '\n';
                    std::cout << "Number of Classes (max of 4): " << info[1] << '\n';
                    std::cout << "Class Name" << std::setw(16) << "Class Time" << std::setw(16) << "Days Met\n";
                    for(int i = 2; i < info.size(); i+= 3)
                    {
                        std::cout <<std::setw(10) << info[i] << std::setw(16) << info[i+1] << std::setw(15) << info[i+2] << '\n';
                    }
                    std::cout << '\n';
                }
                break;
            }

            case 3:
            {
                std::vector <std::string> info = student1.get_student("grades.csv", idnum);
                if(info[0] == "1")
                {
                    std::cout << "ERROR, no schedule found for " << idnum << '\n';
                }
                else
                {
                    std::cout << "Student ID number: " << info[0] << '\n';
                    std::cout << std::setw(8) <<  "Class name" << std::setw(9) << "Grade\n";
                    for(int i = 1; i < info.size(); i+=2)
                    {
                        std::cout << std::setw(8) << info[i] << std::setw(8) << info[i+1] << '\n';
                    }
                }
                break;
            }
            case 4:
                return;

        }
    }
}