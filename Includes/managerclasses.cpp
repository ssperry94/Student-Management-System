#include <managerclasses.h>

//smanage global external variables
std::string smanage::student_path = "CSV Files/maincsvs/students.csv";
std::string smanage::schedule_path = "CSV Files/maincsvs/schedule.csv";
std::string smanage::grade_path = "CSV Files/maincsvs/grades.csv";

// User Class Methods
std::string User::find_student()
{
    std::string name;
    std::cout << "\nPlease enter the student's first and last name: ";
    std::getline(std::cin, name);
    delete_ending_spaces(name);
    std::cout << '\n';

    std::fstream student_file{smanage::student_path, std::ios::in | std::ios::binary};

    if(!student_file)
    {
        return "2";
    }

    std::string student;
    std::string student_info[4];

    while(std::getline(student_file, student))
    {
        std::istringstream line(student);
        for(int i = 0; i < 4; i++)
        {
            std::string element;
            std::getline(line, element, ',');
            student_info[i] = element;
        }   

        if(student_info[1] + ' ' + student_info[2] == name)
        {
            std::cout << "Student successfully found.\n\n";
            return student_info[0]; 
        }
    }
    student_file.close();
    return "1";
}

//will return 1 if it cannot find a entry on the disired folder, regaurdess of whether it is empty or not
std::vector <std::string> User::get_student(std::string filename, std::string idnum)
{
    if(idnum == "1")
    {
        return {};
    }

    std::ifstream schedule{filename};
    std::string student;
    std::vector <std::string> student_arr;

    //creates a vector with disired student from their ID number
    while(std::getline(schedule, student))
    {
        std::stringstream line(student);
        std::string element;
        while(std::getline(line,element,','))
        {
            student_arr.push_back(element);
        }
        if(student_arr[0] == idnum)
        {
            break;
        }
        else
        {
            student_arr.clear();
        }
    }

    if(student_arr.empty())
    {
        student_arr.push_back("1");
        return student_arr;
    }
    //because vector will have blank spaces if student isn't taken the max of 4 classes, this algo deletes those spaces

    for(int i = 0; i < student_arr.size(); i++)
    {
        if(student_arr[i] == " ")
        {
            student_arr.erase(student_arr.begin() + i);
        }
    }
    student_arr.shrink_to_fit();
    schedule.close();

    return student_arr;
}

//for all input that is 1 number, checks to make sure that is the case
bool User::check_input(std::string container)
{
    if(container.length() > 1)
    {
        return false;
    }
    if(!isdigit(container[0]))
    {
        return false;
    }
    return true;
}

//deletes any accidental ending spaces that throws off file-reading/writing
void User::delete_ending_spaces(std::string &string)
{
    int last = string.length() - 1;
    if(string[last] != ' ')
    {
        return;
    }

    else
    {
        string.pop_back();
        return delete_ending_spaces(string);
    }
}

//Student Class Methods
Student::Student(std::string &idnum)
{
    this->idnum = idnum;
}

std::string Student::get_idnum()
{
    return idnum;
}

// Teacher Class Methods
const int Teacher::generate_ID()
{
    std::random_device rd;
    std::mt19937 gen(rd() ^ std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution <int> dist(1000000,9999999);

    return dist(gen); 

}

int Teacher::write_to_outfile(std::vector<std::string> vector, std::string outfile_path)
{
    std::fstream file;
    file.open(outfile_path, std::ios::app);

    if(!file)
    {
        std::cout << "File could not be opened.\n";
        return 1;
    }

    for(std::string item : vector)
    {
        file << item << ',';
    }

    file << '\n';
    file.close();
    return 0;
}

void Teacher::addStudent()
{
    std::vector <std::string> student_info;
    std::string firstname, lastname, birthday;

    std::cout << "Enter student's Firstname: ";
    std::cin >> firstname;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter student's Lastname: ";
    std::cin >> lastname;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter student's Date of Birth: ";
    std::cin >> birthday;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    const int idnum = generate_ID();
    std::string s_idnum = std::to_string(idnum);

    student_info.push_back(s_idnum);
    student_info.push_back(firstname);
    student_info.push_back(lastname);
    student_info.push_back(birthday);

    int error_check = write_to_outfile(student_info, smanage::student_path);
    if(error_check == 0)
    {
        std::cout << "\nData successfully added.\n";
    }
    else
    {
        std::cerr << "An error has occured during the file-writing process.\n";
    }
}

void Teacher::add_student_schedule(std::string idnum)
{
    std::vector <std::string> schedule;
    if(idnum == "1")
    {
        std::cout << "ERROR: no student with that ID number was found.\n";
        return;
    }
    schedule.push_back(idnum);

    int classes_num;

    do
    {
        std::cout << "Please enter the amount of classes the student is taking this year: ";
        std::cin >> classes_num;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if(classes_num > 4)
        {
            std::cout << "Please make sure the student isn't taking more than 4 classes.\n";
        }

    } while(classes_num > 4);

    std::string s_classes_num = std::to_string(classes_num);

    schedule.push_back(s_classes_num);

    for(int i = 1; i <= classes_num; i++)
    {
        std::string classes;
        std::string time;
        std::string days_of_week;

        std::cout << "Please enter the class the student is taking: ";
        std::cin >> classes;
        schedule.push_back(classes);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Please enter the starting and ending time (HH:MM-HH:MM): ";
        std::cin >> time; 
        schedule.push_back(time);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Please enter the days of week: ";
        std::cin >> days_of_week;
        schedule.push_back(days_of_week);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    int error_check = write_to_outfile(schedule, smanage::schedule_path);
    if(error_check == 0)
    {
        std::cout << "Data successfully added.\n";
    }
    else
    {
        std::cerr << "An error has occured during the file-writing process.\n";
    }
}

void Teacher::add_grades(std::string idnum)
{
    std::vector <std::string> schedule = get_student(smanage::schedule_path, idnum), grades;
    if(idnum == "1")
    {
        std::cout << "ERROR: no student with that ID number was found.\n";
        return;
    }
    grades.push_back(idnum);

    for(int i = 2; i < schedule.size(); i += 3)
    {
        std::string grade;
        grades.push_back(schedule[i]);
        std::cout << "Please enter the grade for " << schedule[i] << ": ";
        std::cin >> grade;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        grades.push_back(grade);
    }
    int error_checker = write_to_outfile(grades, smanage::grade_path);
    if(error_checker == 0)
    {
        std::cout << "Data entered successfully.";
    }
    else
    {
        std::cerr << "An error has occured during the file-writing process.\n";
    }
}

void Teacher::reset()

{
    std::ofstream student_info{smanage::student_path};
    student_info << "Student ID Number,";
    student_info << "Firstname,";
    student_info << "Lastname,";
    student_info << "DOB,\n";
    student_info.close();

    std::ofstream student_schedule{smanage::schedule_path};
    student_schedule << "Student ID Number,";
    student_schedule << "Amount of Classes Taken,";
    student_schedule << "Class Name,";
    student_schedule << "Class Time,";
    student_schedule << "Days of the Week,";
    student_schedule << "Class Name,";
    student_schedule << "Class Time,";
    student_schedule << "Days of the Week,";
    student_schedule << "Class Name,";
    student_schedule << "Class Time,";
    student_schedule << "Days of the Week,";
    student_schedule << "Class Name,";
    student_schedule << "Class Time,";
    student_schedule << "Days of the Week,\n";
    student_schedule.close();

    std::ofstream student_grades{smanage::grade_path};
    student_grades << "Student ID Number,";
    student_grades << "Class Name,";
    student_grades << "Class Grade,";
    student_grades << "Class Name,";
    student_grades << "Class Grade,";
    student_grades << "Class Name,";
    student_grades << "Class Grade,";
    student_grades << "Class Name,";
    student_grades << "Class Grade,\n";
}

void Teacher::reset(std::string filename)
{
    if(filename != "students.csv" && filename != "schedule.csv" && filename != "grades.csv")
    {
        std::cout << "\nFile does not exist.\n";
        return;
    }
    std::ofstream file{filename};

    if(!file)
    {
        std::cout << "\nCould not open file.\n";
        return;
    } 
    

    if(filename == "students.csv")
    {
        char user_input;
        std::cout << "Reseting students.csv may cause some of the other files to misbehave, are you sure you wish to proceed?(Y/N)\n";
        std::cin >> user_input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if(user_input == 'Y' || user_input == 'y')
        {
            file << "Student ID Number,";
            file << "Firstname,";
            file << "Lastname,";
            file << "DOB,\n";
        }
        else if(user_input == 'N' || user_input == 'n')
        {
            std::cout << "Returing to main menu...\n\n";
            file.close();
            return;
        }
        else
        {
            std::cout << "Input not recognized, returning to main menu.\n\n";
            file.close();
            return;
        }
    }

    else if(filename == "schedule.csv")
    {
        file << "Student ID Number,";
        file << "Amount of Classes Taken,";
        file << "Class Name,";
        file << "Class Time,";
        file << "Days of the Week,";
        file << "Class Name,";
        file << "Class Time,";
        file << "Days of the Week,";
        file << "Class Name,";
        file << "Class Time,";
        file << "Days of the Week,";
        file << "Class Name,";
        file << "Class Time,";
        file << "Days of the Week,\n";
    }
    else if(filename == "grades.csv")
    {
        file << "Student ID Number,";
        file << "Class Name,";
        file << "Class Grade,";
        file << "Class Name,";
        file << "Class Grade,";
        file << "Class Name,";
        file << "Class Grade,";
        file << "Class Name,";
        file << "Class Grade,\n";
    }
    
    file.close();
    std::cout << "\nReset " << filename << " successfully.";
}