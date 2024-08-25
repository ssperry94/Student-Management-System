Login Information: 
Teacher:
    -Username: teacher
    -Password: teacher123

Students:
    -use either of the following:
        For Student 1:
        -Username: johnsmith
        -Password: johnsmith123

        For Student2:
        -Username: janedoe
        -Password: janedoe123


Build Rough (Windows) Draft:
1) clone the repo with <command to clone>
2) go to https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-cmd to set up vcpgk package manager (if not already)

3) cd into the vcpkg directory and download the Cryptopp library from vcpkg with this command: vcpkg install cryptopp:x64-windows-static-md (for MSVC compiler)

for G++: vcpkg install cryptopp_x64-mingw-static

4) If using cmake from the CMD, follow these commands:
    -mkdir build && cd build 
    -cmake ..
    -cmake --build .
    -cd ../bin
    -StudentManager

For Linux:
1) Install cmake for linux
2) Install cryptopp for linux with this command: sudo apt-get install libcrypto++-dev libcrypto++-doc libcrypto++-utils
3) 