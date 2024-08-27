# StudentManager

**A cross-platform solution for students and teachers to manage their day-to-day activities.**

## Description

StudentManager is a user-friendly application designed to help teachers efficiently manage their students' information and provide students with easy access to their grades and schedules.

**Key Features:**

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
  - [Installation Guide for vcpkg](https://github.com/microsoft/vcpkg#quick-start)

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
    cd ../bin
    StudentManager
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
    cd ../bin
    ./StudentManager
    ```