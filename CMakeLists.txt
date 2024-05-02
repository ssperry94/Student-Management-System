#for Student Manager

cmake_minimum_required(VERSION 3.13.0)
project(StudentManager)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(os_type 64)

#setting debug code to match that of crypto++
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /D_ITERATOR_DEBUG_LEVEL=2")

#setting path straight to cryptopp .lib file
set(CryptoLibDir "C:/Users/ssper/OneDrive/Desktop/CPP/Projects/Student Managerv2/vcpkg/packages/cryptopp_x64-windows/lib")
file(GLOB CryptoLibFiles "${CryptoLibDir}/*")
message(STATUS "Crypto library files: ${CryptoLibFiles}")



link_directories(${CryptoLibDir})
include_directories("${CryptoLibDir}")
include_directories("C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/shared")
include_directories("C:/Users/ssper/OneDrive/Desktop/CPP/Projects/Student Managerv2")
include_directories("C:/Users/ssper/OneDrive/Desktop/CPP/Projects/Student Managerv2/vcpkg/packages/cryptopp_x64-windows/include/cryptopp")

set(SOURCES main.cpp source.cpp)


add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE cryptopp)
