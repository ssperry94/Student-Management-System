# StudentManager

A cross-platform solution for students and teachers to manage their day-to-day activities.
# Description

StudentManager is a user-friendly application designed to help teachers efficiently manage their students' information and provide students with easy access to their grades and schedules.

Key Features:

    For Students: 
        Students can quickly view their personal information, grade averages, and class schedules, making it easier to stay on top of their academic performance.
    For Teachers: 
        Teachers can manage all student records, including adding new students, updating grades, and scheduling classes. This helps streamline administrative tasks and ensures accurate record-keeping.


## Build Information

# Dependancies
    For all platforms:
        -A C++ compiler
            either g++ for windows or linux, or MSVC for windows
        -CMake
            download: https://cmake.org/download/

        Crypto++ library for your OS

    For Windows only:
        -vcpkg manager to get Crypto++

# How To Build 
For Windows:
1) Clone this repository with: 
        git clone https://github.com/ssperry94/Student-Management-System

2) Head to https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-cmd and follow the first section to set up vcpkg in this project's directory.

3) cd into the new vcpkg directory and run one of the following commands:
-For MSVC Compilers:
        install cryptopp:x64-windows-static-md

For G++ Compilers:
        vcpkg install cryptopp_x64-mingw-static

4) If you're building from the command line, use the following set of commands:
        -mkdir build && cd build 
        -cmake .. 
        -cmake --build . 
        -cd ../bin 
        -StudentManager

Otherwise just have you're code editor/IDE configured with CMake and build.

For Linux:
1) Clone this repository with: 
        git clone https://github.com/ssperry94/Student-Management-System

2) Install CMake for Linux
3) Get the Crypto++ library with:
        sudo apt-get install libcrypto++-dev libcrypto++-doc libcrypto++-utils

4) If you're building from a bash terminal, use the following commands after cd into the projects main directory:
        mkdir build && cd build 
        cmake .. 
        cmake --build . 
        cd ../bin 
        ./StudentManager
