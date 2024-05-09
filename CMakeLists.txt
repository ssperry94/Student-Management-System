#for Student Manager

cmake_minimum_required(VERSION 3.13.0)
project(StudentManager)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(os_type 64)


#setting path straight to cryptopp .lib file
set(CryptoLibDir "C:/Users/ssper/OneDrive/Desktop/CPP/Projects/Student Managerv2/vcpkg/packages/cryptopp_x64-mingw-static/lib")

#setting path to source files and headers
set(SourceFileDir "${CMAKE_SOURCE_DIR}/Includes")


link_directories(${CryptoLibDir})
include_directories("${CryptoLibDir}")
include_directories("C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/shared")
include_directories("C:/Users/ssper/OneDrive/Desktop/CPP/Projects/Student Managerv2")
include_directories("C:/Users/ssper/OneDrive/Desktop/CPP/Projects/Student Managerv2/vcpkg/packages/cryptopp_x64-mingw-static/include/cryptopp")
include_directories("${SourceFileDir}")


set(SOURCES main.cpp ${SourceFileDir}/managerclasses.cpp ${SourceFileDir}/user_auth.cpp ${SourceFileDir}/handling.cpp)


add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE cryptopp)
