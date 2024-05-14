#ifndef HANDLING_H
#define HANDLING_H

#include <managerclasses.h>
#include <user_auth.h>
#include <iomanip>

//main functions for handling each options
void handle_teacher_options();
void handle_student_options();
void handle_logging_in();
void handle_logging_in(std::string &idnum);
void handle_registration(bool is_teacher);

#endif 