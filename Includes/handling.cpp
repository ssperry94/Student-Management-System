#include <handling.h>

void handle_teacher_options()
{
    Teacher teacher1;

    //breaks when user is verified
    while(true)
    {
        char user_verify_option;
        std::cout << "Would you like to log in, register a new account, or quit?(L/R/Q): ";
        std::cin.get(user_verify_option);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if(user_verify_option == 'L' || user_verify_option == 'l')
        {
            handle_logging_in();
            utils::pause();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break; //end loop
        }

        else if(user_verify_option == 'R' || user_verify_option == 'r')
        {
            handle_registration(true);
            std::cout << "User registered successfully!\n";
        }

        else if(user_verify_option == 'Q' || user_verify_option == 'q')
        {
            return; //leaves function and returns to main
        }

        else
        {
            std::cout << "Improper input detected, please enter either 'L', 'R', or 'Q'. It is not case-sensitive.\n";
            //std::cin.sync();
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    //main loop that handles teacher options once logged in
    while(true)
    {
        //stores input first as a string, then ensures that input will not cause a crash
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

            //main options
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

                    if(idnum == "2")
                    {
                        std::cout << "Check infile path.\n";
                        exit(1);
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
                    utils::pause();
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
                    utils::pause();
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
                    utils::pause();
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
    //idnum that will become stduent class's idnumber
    std::string idnum;

    while(true)
    {
        char user_verify_option;

        std::cout << "Would you like to log in, register a new account, or quit?(L/R/Q): ";
        std::cin.get(user_verify_option);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if(user_verify_option == 'L' || user_verify_option == 'l')
        {
            handle_logging_in(idnum);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            utils::pause();
            break;
        }
        else if(user_verify_option == 'R' || user_verify_option == 'r')
        {
            handle_registration(false);
            std::cout << "User registered successfully!\n";
        }

        else if(user_verify_option == 'Q' || user_verify_option == 'q')
        {
            return;
        }

        else
        {
            std::cout << "Improper input detected, please enter either 'L', 'R', or 'Q'. It is not case-sensitive.\n";
        }
    }

    Student student1(idnum);
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
                    utils::pause();
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
                    utils::pause();
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
                    utils::pause();
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

//for teachers
void handle_logging_in()
{
    //initalize key
    constexpr size_t AES_KEY_SIZE = 256 / 8;
    std::vector <uint8_t> key(AES_KEY_SIZE);
    
    //populate key vector
    smanEncrypt::retrieve_key(key);

    int tries = 0;
    while(tries != 3)
    {
        std::string username, password;
        std::string actual_username, actual_password;
        std::streampos current_pos = std::ios::beg;

        //get username and password
        std::cout << "Please enter your username and password:\nUsername: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;
        std::cin.sync();

        smanEncrypt::LoggingIn user_login_handler(true, username, password);
        while(true)
        {
            std::vector <uint8_t> iv(CryptoPP::AES::BLOCKSIZE);
            user_login_handler.retreive_account(actual_username, actual_password, iv, current_pos);

            if(current_pos == -1)
            {
                break; //means end of file was reached
            }
            
            if(smanEncrypt::decrypt(actual_username, key, iv) == username && smanEncrypt::decrypt(actual_password, key, iv) == password)
            {
                std::cout << "Success! Logging in..." << '\n';
                return; //user is verified
            }
        }
        std::cout << "Incorrect username/password. Please try again.\n";
        tries++;
        current_pos = std::ios::beg;
    }   
}

//for students
void handle_logging_in(std::string &idnum)
{
    constexpr size_t AES_KEY_SIZE = 256 / 8;
    int tries = 0;
    std::vector <uint8_t> key(AES_KEY_SIZE);
    

    //populate key vector
    smanEncrypt::retrieve_key(key);

    while(tries != 3)
    {
        std::string username, password;
        std::string actual_username, actual_password;
        std::streampos current_pos = std::ios::beg;

        //get username and password
        std::cout << "Please enter your username and password:\nUsername: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;
        std::cin.sync();

        smanEncrypt::LoggingIn user_login_handler(false, username, password);
        while(true)
        {
            std::vector <uint8_t> iv(CryptoPP::AES::BLOCKSIZE);

            //in order to avoid sending the wrong id to main, will send id to this variable, who will then send it to idnum upon verification
            std::string idnum_hold;

            user_login_handler.retreive_account(actual_username, actual_password, iv, idnum_hold, current_pos);

            if(current_pos == -1)
            {
                break;
            }
            
            if(smanEncrypt::decrypt(actual_username, key, iv) == username && smanEncrypt::decrypt(actual_password, key, iv) == password)
            {
                std::cout << "Success! Logging in..." << '\n';
                idnum = smanEncrypt::decrypt(idnum_hold, key, iv);
                return;
            }
        }
        std::cout << "Incorrect username/password. Please try again.\n";
        tries++;
        current_pos = std::ios::beg;
    }   
}

//is_teacher should be false for students, true for teacher
void handle_registration(bool is_teacher)
{
    constexpr size_t AES_KEY_SIZE = 256 / 8;
    std::vector <uint8_t> key(AES_KEY_SIZE);
    smanEncrypt::retrieve_key(key);

    //ask for username and password

    std::string username, password;
    std::cout << "Pleased enter your desired username: ";
    std::cin >> username;
    std::cin.ignore(std::numeric_limits<std::streampos>::max(), '\n');

    do
    {
        std::string attempt_1, attempt_2;
        std::cout << "Please enter your password: ";
        std::cin >> attempt_1;
        std::cin.ignore(std::numeric_limits<std::streampos>::max(), '\n');
        std::cout << "Please confirm your password: ";
        std::cin >> attempt_2;
        std::cin.ignore(std::numeric_limits<std::streampos>::max(), '\n');

        if(attempt_1 == attempt_2)
        {
            std::cout << "Passwords match! Registering user...\n";
            password = attempt_1;
            break;
        }

        std::cout << "Passwords do not match, please retry.\n";
    } while(true);

    //created UserRegistrator class
    smanEncrypt::UserRegistrator registrator(is_teacher, username, password);
    //add account
    int error = registrator.add_account(key);
    if(error == 1)
    {
        std::cerr << "User not successfully registred, exiting program...";
        exit(1);
    }
}

