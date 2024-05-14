#for Student Manager

cmake_minimum_required(VERSION 3.13.0)
project(StudentManager)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(os_type 64)


#setting path straight to cryptopp .lib file
#set(CryptoLibDir "C:/Users/ssper/OneDrive/Desktop/CPP/Projects/Student Managerv2/vcpkg/packages/cryptopp_x64-mingw-static/lib")
set(CryptoLibDir "${CMAKE_SOURCE_DIR}/bin/staticlibs")

#setting path to source files and headers
set(SourceFileDir "${CMAKE_SOURCE_DIR}/Includes")

#setting path to bin folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

link_directories(${CryptoLibDir})
include_directories(${CSVFileDir})
include_directories("${CryptoLibDir}")
include_directories("C:/Users/ssper/OneDrive/Desktop/CPP/Projects/Student Managerv2")
include_directories("C:/Users/ssper/OneDrive/Desktop/CPP/Projects/Student Managerv2/vcpkg/packages/cryptopp_x64-mingw-static/include/cryptopp")
include_directories("${SourceFileDir}")


set(SOURCES main.cpp ${SourceFileDir}/managerclasses.cpp ${SourceFileDir}/user_auth.cpp ${SourceFileDir}/handling.cpp)


add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE cryptopp)
