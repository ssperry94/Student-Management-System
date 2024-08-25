#for Student Manager

cmake_minimum_required(VERSION 3.13.0)
project(StudentManager)


if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
    if(CMAKE_COMPILER_IS_GNUCXX)
        set(CryptoLibDir "${CMAKE_SOURCE_DIR}/vcpkg/packages/cryptopp_x64-mingw-static/lib")
        set(CryptoSourceDir "${CMAKE_SOURCE_DIR}/vcpkg/packages/cryptopp_x64-mingw-static/include")
    elseif(MSVC)
        set(CryptoLibDir "${CMAKE_SOURCE_DIR}/vcpkg/packages/cryptopp_x64-windows-static-md/debug/lib/")
        set(CryptoSourceDir "${CMAKE_SOURCE_DIR}/vcpkg/packages/cryptopp_x64-windows-static-md/include")
    endif()
endif()

#setting path to source files and headers
set(SourceFileDir "${CMAKE_SOURCE_DIR}/Includes")

#setting path to bin folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin)

link_directories(${CryptoLibDir})
# include_directories(${CSVFileDir})
#include_directories("${CryptoLibDir}")
include_directories("${SourceFileDir}")
if(WIN32)
    include_directories("${CryptoSourceDir}")
endif()

set(SOURCES main.cpp ${SourceFileDir}/managerclasses.cpp ${SourceFileDir}/user_auth.cpp ${SourceFileDir}/handling.cpp ${SourceFileDir}/utils.cpp)


add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE cryptopp)
