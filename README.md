# StudentManager

**A cross-platform solution for students and teachers to manage their day-to-day activities.**

## Disclaimer
==This project is only intended for demonstrational purposes, and should NEVER be used to manage actual students or store sensitive information.==

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

**For all platforms:**
- **C++ Compiler**
  - GCC (g++) for Linux
  - MSVC or MinGW for Windows
- **CMake**
  - [Download CMake here](https://cmake.org/download/)
- **Crypto++ Library**
  - Platform-specific installation instructions provided below.

**For Windows only:**
- **vcpkg Package Manager**
  - [Installation Guide for vcpkg](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-cmd)

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

3. **No Editing Capability**: At this time, there is no way to edit information once it has been entered. This means that any data entered for students or teachers is permanent. The only way to correct it is by accessing the "Troubleshoot" option in the main menu and resetting the affected files. Be aware that resetting files containing pre-made students and teachers will delete them.

4. **No GUI**: The program currently operates entirely through the terminal. While the program includes error handling for most invalid inputs, it may not catch all potential errors.


## Tutorial 
To run the project, you can either run the code from your development enviornment of choice (assuming you've set up the dependancies), or run one of these commands:
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

**Teacher**
- Username: teacher
- Password: teacher123

**Student**
- Username: johnsmith
- Password: johnsmith123

*OR*

- Username: janedoe
- Password: janedoe123

Alternativly, if you wish to test the registration system, press 'R' and follow the prompts to register as a student or teacher. This will add login information to the respective login CSVs. 

Assuming you've successfully logged on, you can now mess with the various options avalible. If the program asks for students firstname and lastname, and you're using the pre-made students, their first names are:

    - John Smith
    - Jane Doe

From here, you can explore the program and follow the prompts. Keep in mind the limitations of the program since this is only for demostration purposes. 
## Known Issues:

- When using MinGW on windows, when making it past the inital menu, the user has to hit enter twice

