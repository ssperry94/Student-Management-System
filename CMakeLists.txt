#for Student Manager

cmake_minimum_required(VERSION 3.13.0)
project(StudentManager)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

#setting path straight to cryptopp .lib file
#set(CryptoLibDir "${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-windows/lib")

#setting crypto++ dependancy
#link_directories(CryptoLibDir)
include_directories("C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/shared")
include_directories("C:/Users/ssper/OneDrive/Desktop/CPP/Projects/Student Managerv2")
include_directories("C:/Users/ssper/OneDrive/Desktop/CPP/Projects/Student Managerv2/vcpkg/installed/x64-windows/include")

set(os_type 64)


set(FullOutputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}${os_type}/${CMAKE_BUILD_TYPE}")
set(ExeOutputDir "${CMAKE_SOURCE_DIR}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static libs")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

include_directories("${FullOutputDir}/staticlibs")


add_library(source source.cpp)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE source PUBLIC cryptopp.lib)
