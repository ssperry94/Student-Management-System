#ifndef MANAGERCLASSES_H
#define MANAGERCLASSES_H



//Libraries
#include <chrono>
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <sstream>
#include <vector>
#include <string>
#include <limits>

namespace smanage
{
    extern std::string student_path;
    extern std::string schedule_path;
    extern std::string grade_path;
};
//class for shared methods between students and teachers
class User
{
    public:
        //returns all information about student inside of a vector to be processed later
        std::vector <std::string> get_student(std::string filename, std::string idnum);

        //returns student id number from students.csv        
        std::string find_student();

        //validates input feed into both the teacher function and the student function
        //returns false if length of input > 1 and if the first character isn't a number, true if only 1 number detected
        bool check_input(std::string container);

        //if a user accidentally leaves a space at the end of their input, function will delete the last index until it runs across a character
        //that is not a spacee
        void delete_ending_spaces(std::string &string);
};

//contains data and methods relevent to students
class Student : public User
{
    private:
        std::string idnum;
    public:
        
        //constructor used to set idnum member to a decrypted idnum found on student_login.csv
        Student(std::string &idnum);

        //getter for idnum memberf
        std::string get_idnum();
};

//contains data and methods relvenent to teachers
class Teacher : public User
{
    private:
        //generates the student ID for new students
        const int generate_ID();

        int write_to_outfile(std::vector<std::string> vector, std::string outfile_path);
    public:
        //overloaded reset function that can reset any files that are misbehaving
        void reset();
        //overloaded reset function that resets the specific file
        void reset(std::string filename);

        //adds a new student to student.csv
        void addStudent();

        //adds a new schedule for an existing student on schedule.csv
        void add_student_schedule(std::string idnum);

        //adds grades for an existing student to grades.csv
        void add_grades(std::string idnum);
};

#endif