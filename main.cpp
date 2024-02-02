#include <iostream>
#include <C:\Users\ssper\OneDrive\Desktop\CPP\Projects\Student Managerv2\managerclasses.h>

//maybe make a python script to verify user info? 
//should see about maybe making a GUI at some point
//should put on Git soon
//write real documentation on how to use, functions, etc

//CURRENTLY: testing out methods for each class

void print_vector(std::vector <std::string> vector)
{
    std::cout << "{";
    for(std::string item : vector)
    {
        std::cout << item << ", ";
    }
    std::cout << "}\n";
}

int main()
{


    return 0;
}