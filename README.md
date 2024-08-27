# StudentManager

**A cross-platform solution for students and teachers to manage their day-to-day activities.**

## Disclaimer
**This project is only intended for demonstrational purposes, and should NEVER be used to manage actual students or store sensitive information.**

## Description

StudentManager is a user-friendly application designed to help teachers efficiently manage their students' information and provide students with easy access to their grades and schedules.

**Do not use this project to store any information on any real students or teachers, nor should you store any actual login information through this application.**

**Key Features:**

- All user information is encrypted using Crypto++ to protect sensitive information.
- **For Students:**
  - Quickly view personal information, grade averages, and class schedules, making it easier to stay on top of academic performance.

- **For Teachers:**
  - Manage all student records, including adding new students, updating grades, and scheduling classes. This helps streamline administrative tasks and ensures accurate record-keeping.
## Build Information

### Dependencies

**Linux**
- **C++ Compiler**: GCC (g++) for Linux
- **CMake**: [Download CMake here](https://cmake.org/download/)
- **Crypto++ Library**: Platform-specific installation instructions provided below.

**Windows**
- **C++ Compiler**: MinGW or MSVC
- **CMake**: [Download CMake here](https://cmake.org/download/)
- **Crypto++ Library**: Platform-specific installation instructions provided below.
- **vcpkg Package Manager**: [Installation Guide for vcpkg](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-cmd)

### How To Build

#### **Windows**

1. **Clone the Repository:**
   ```bash
        git clone https://github.com/ssperry94/Student-Management-System
        cd Student-Management-System
   ```
2. **Install vcpkg on Windows**
3. **Install Crypto++:**
    - **For MSVC Compilers:**
        ```bash
        cd vcpkg
        vcpkg install cryptopp:x64-windows-static-md
        ```
    - **For G++ Compilers:**
        ```bash
        cd vcpkg
        vcpkg install cryptopp_x64-mingw-static
        ```

4. **Build the Project:**
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```
*Alternatively, configure your code editor/IDE with CMake and build within the environment.*

#### For Linux:

1. **Clone the Repository:**
    ```bash
    git clone https://github.com/ssperry94/Student-Management-System
    cd Student-Management-System
    ```

2. **Install CMake for Linux:**
    ```bash
    sudo apt-get install cmake
    ```

3. **Install Crypto++ Library:**
    ```bash
    sudo apt-get install libcrypto++-dev libcrypto++-doc libcrypto++-utils
    ```

4. **Build the Project:**
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

## Limitations

Before running StudentManager, please be aware that this is only for demonstration purposes only. Therefore, there are some limitations you should be aware of:

1. **Duplication**: There is currently no system in place to check for duplicate information. This includes any data entered for students, teachers, usernames, and passwords. Adding duplicates of pre-existing information may lead to errors.

2. **.key File**: The encryption key is stored in a `.key` file located under `bin/key`. Do not change or delete this file, as doing so will prevent you from accessing anything past the login screen.

3. **No Editing Capability**: At this time, there is no way to edit information once it has been entered. This means that any data entered for students or teachers is permanent. The only way to correct it is by accessing the "Troubleshoot" option in the main menu and resetting the affected files. Be aware that resetting files containing pre-made students and teachers will delete them. This feature will be added at a later date.

4. **No GUI**: The program currently operates entirely through the terminal. While the program includes error handling for most invalid inputs, it may not catch all potential errors.


## Tutorial 
To run the project, you can either run the code from your development enviornment of choice (assuming you've set up the dependancies), or run one of these commands from the project directory:
### **Windows**
    ```bash
        cd ../bin
        StudentManager
    ```
### **Linux**
    ```bash
        cd ../bin
        ./StudentManager
    ```

The program should then ask if you are a teacher or a student. By default there is one teacher and two students. You can log in as either, below is the login information

**Teacher Login:**
- **Username:** teacher
- **Password:** teacher123

**Student Logins:**
- **Username:** johnsmith
- **Password:** johnsmith123

- **Username:** janedoe
- **Password:** janedoe123


Alternativly, if you wish to test the registration system, press 'R' and follow the prompts to register as a student or teacher. This will add login information to the respective login CSVs. 

Assuming you've successfully logged on, you can now mess with the various options avalible. If the program asks for students firstname and lastname, and you're using the pre-made students, their first and last names are:

    - John Smith
    - Jane Doe

From here, you can explore the program and follow the prompts. Keep in mind the limitations of the program since this is only for demostration purposes. 

## About the Code 

Student Manager is made in C++, using CMake as the build system. All data for demonstration purposes is written to and saved to CSV files. The CSV files for student data can be found under `bin/CSV Files/maincsvs`. The login information for both students can be found under `bin/CSV Files/logincsvs`. The login data is encrypted with Crypto++, and needs the `.key` file to unlock - all of which is handled through the app. 

Here's a small summary of each source file:
- **main.cpp:** The entry point for StudentManager. It will determine if you are a student or a teacher, then send you to the proper menu
- **handling.cpp:** These contain functions that display the menu and instantiante instances of student and teacher classes, as well as functions that display the login menu and call the various user authenication classes and functions. 
- **user_auth:** This source file contains all the classes and functions that handle user authentication. The encryption library is Crypto++. It uses the AES to encrypt the data and CBC to ensure there are no repeating characters. Each Initalization Vector is stored alongside its respective login information for demonstration purposes. 
- **managerclasses.cpp:** This contains the classes for teachers and students, as well as the user class they both inherit from. These classes handle all options related to teachers and students.
-**utils.cpp:** Contains any utility type functions- as of now there is only the pause() function, which is a function that can pause the terminal on both Windows and Linux. As more features are added, this source file will grow as needed. 

### What I Learned

This project was my first introduction into C++, and it became a pivotal experience in my journey as a developer. Through StudentManager, I not only learned the fundamentals of C++ programming but also delved into the complexities of building a cross-platform application from the ground up.

#### Key Points
- **Mastery of C++:** This project provided a solid foundation in C++, allowing me to become familiar with the language's syntax, data structures, and object-oriented features. I gained experience with the C++ Standard Library, particularly in managing data collections and handling file operations. This project helped me understand the nuances of C++ and laid the groundwork for more advanced topics in future projects.

- **Integrating My First Build System:** For this project, I had to delve deep into build systems and really try to understand how the C++ compiler works.This led me to learn how to structure a project directory for scalability and maintainability. This knowledge has since become a cornerstone of my approach to developing robust software, and is now the first item I consider when beginning a new project.

- **Integrating Third-Party Libraries:** Integrating Crypto++ had a significant learning curve. I learned there were many nuances to how a library is compiled and integrated in C++. By overcoming this challenge, I became confidnet in integrating third-party libraries into a project, configuring them for different operating systems, and ensuring consistent functionality across platforms.

- **Encryption and Documentation:** Implementing encryption with Crypto++ not only introduced me to the intricacies of cryptographic algorithms but also honed my ability to navigate and apply complex documentation. This experience has enhanced my confidence in working with unfamiliar codebases and technologies.

- **Transferable Skills:** The skills I acquired during this project—ranging from C++ programming and project management to cross-platform development and encryption—have been invaluable in my subsequent projects, both personal and academic. These experiences have laid a solid foundation for my growth as a software developer.

### What Can Be Improved 

- **Refactoring:** Currently, the codebase would benefit from a refactoring to improve its maintainability and scalability. For example, the Student and Teacher classes have too many responsibilities and should have some of their methods moved into separate classes to adhere to good programming practices. 

- **Abstract Classes:** The User and UserCommon classes would be better served as abstract classes since they shouldn't be instantiated. Most of their methods could be virtual, making it easier to manage the shared functionality between Student and Teacher.

- **Error Handling:** While most errors have a way to be handled, the use of try-catch statements and exceptions would make for much better and flexible error handling than the current system. 

## Known Issues:

- When using MinGW on windows, when making it past the inital menu, the user has to hit enter twice.

