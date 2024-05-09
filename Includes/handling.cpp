#include <handling.h>

void handle_teacher_options()
{
    Teacher teacher1;
    char user_verify_option;

    std::cout << "Would you like to log in, or register a new account?(L/R): ";
    std::cin.get(user_verify_option);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if(user_verify_option == 'L' || user_verify_option == 'l')
    {
        //function for logging in
    }
    else if(user_verify_option == 'R' || user_verify_option == 'r')
    {
        //function for registering new account
    }
    while(true)
    {
        std::string container;

        std::cout << "\nPlease select which action you would like to take:\n";
        std::cout << "1. Add a new student\n";
        std::cout << "2. Enter a students schedule\n";
        std::cout << "3. Enter grades\n";
        std::cout << "4. View Student information\n";
        std::cout << "5. View student schedule\n";
        std::cout << "6. View student grades\n";
        std::cout << "7. Troubleshoot\n";
        std::cout << "8. Quit\n\n";
        std::getline(std::cin, container);
        if(teacher1.check_input(container))
        {
            int user_response = stoi(container);
            switch(user_response)
            {
                case 1:
                {
                    teacher1.addStudent();
                    break;
                }

                case 2:
                {
                    std::string idnum = teacher1.find_student();
                    teacher1.add_student_schedule(idnum);
                    break;               
                }

                case 3:
                {
                    std::string idnum = teacher1.find_student();
                    teacher1.add_grades(idnum);
                    break;
                }

                case 4:
                {
                    std::string idnum = teacher1.find_student();
                    if(idnum == "1")
                    {
                        std::cout << "No Student ID Number was found.\n\n";
                        break;
                    }
                    std::vector <std::string> info = teacher1.get_student(smanage::student_path, idnum);
                    if(info.empty())
                    {
                        std::cout << "No student ID was found.\n";
                    }
                    else
                    {
                        std::cout << "ID Number: " << info[0] << '\n';
                        std::cout << "First Name: " << info[1] << '\n';
                        std::cout << "Last Name: " << info[2] << '\n';
                        std::cout << "Date of Birth: " << info[3] << "\n\n";
                    }
                    std::system("pause");
                    break;
                }

                case 5:
                {
                    std::string idnum = teacher1.find_student();
                    std::vector <std::string> info = teacher1.get_student(smanage::schedule_path, idnum);
                    if(info.empty())
                    {
                        std::cout << "No student ID was found.\n";
                    }
                    else if(info[0] == "1")
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
                            std::cout << std::left << std::setw(16) << info[i] << std::setw(17) << info[i+1] << std::setw(15) << info[i+2] << '\n';
                        }
                        std::cout << std::right << '\n'; //reseting back to normal
                    }
                    std::system("pause");
                    break;
                }

                case 6:
                {
                    std::string idnum = teacher1.find_student();
                    std::vector <std::string> info = teacher1.get_student(smanage::grade_path, idnum);
                    if(info.empty())
                    {
                        std::cout << "No student ID was found.\n";
                    }
                    else if(info[0] == "1")
                    {
                        std::cout << "ERROR, no grade found for " << idnum << '\n';
                    }
                    else
                    {
                        std::cout << "Student ID number: " << info[0] << '\n';
                        std::cout << std::setw(8) <<  "Class name" << std::setw(9) << "Grade\n";
                        for(int i = 1; i < info.size(); i+=2)
                        {
                            std::cout << std::left << std::setw(13) << info[i] << info[i+1] << '\n';
                        }
                    } 
                    std::cout << std::right; //back to default
                    std::system("pause");
                    break;         
                }

                case 7:
                {
                    std::string filename;
                    std::cout << "\nWhich file do you need reset, or if all files need a reset please enter in all caps ALL: ";
                    std::getline(std::cin, filename);

                    if(filename == "ALL")
                    {
                        teacher1.reset();
                        std::cout << "\nAll files reset.\n" << std::endl;
                    }
                    else
                    {
                        teacher1.reset(filename);
                    }
                    break;
                }

                case 8:
                    return;

                default:
                {
                    std::cout << "Please enter a number 1-8.\n";
                    break;
                }
            }
        }
        else
        {
            std::cout << "Invalid input, please try again.\n";
        }
        std::cin.sync();
    } 
}

void handle_student_options()
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
        std::string container;

        std::cout << "\nPlease select the action you wish to take:\n";
        std::cout << "1. View your information.\n";
        std::cout << "2. View your schedule.\n";
        std::cout << "3. View your grades.\n";
        std::cout << "4. Quit.\n\n";
        std::getline(std::cin, container);
        if(student1.check_input(container))
        {
            int user_response = stoi(container);
            switch(user_response)
            {
                case 1:
                {
                    std::vector <std::string> student_info = student1.get_student(smanage::student_path, idnum);
                    std::cout << "ID Number: " << student_info[0] << '\n';
                    std::cout << "First Name: " << student_info[1] << '\n';
                    std::cout << "Last Name: " << student_info[2] << '\n';
                    std::cout << "Date of Birth: " << student_info[3] << "\n\n";
                    std::system("pause");
                    break;
                }

                case 2:
                {
                    std::vector <std::string> info = student1.get_student(smanage::schedule_path, idnum);
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
                            std::cout << std::left << std::setw(16) << info[i] << std::setw(17) << info[i+1] << std::setw(15) << info[i+2] << '\n';
                        }
                        std::cout << std::right << '\n'; //reseting back to normal
                    }
                    std::system("pause");
                    break;
                }

                case 3:
                {
                    std::vector <std::string> info = student1.get_student(smanage::grade_path, idnum);
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
                            std::cout << std::left << std::setw(13) << info[i] << info[i+1] << '\n';
                        }
                    } 
                    std::cout << std::right; //back to default
                    std::system("pause");
                    break;
                }
                case 4:
                    return;

                default:
                    std::cout << "ERROR! Please select an option 1-4.\n";
                    break;
            }
        }
        else
        {
            std::cout << "Invalid input, please try again.\n";
        }
        std::cin.sync(); 

        std::cout << '\n';

    }
}