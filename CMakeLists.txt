# In case of Debug/Release mode for Makefiles: https://stackoverflow.com/questions/10083427/can-cmake-generate-a-single-makefile-that-supports-both-debug-and-release

####CHANGE OR COMMENT OUT ON DIFFERENT PLATFORMS####
set(CMAKE_C_COMPILER "C:/MinGW64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/MinGW64/bin/g++.exe")


cmake_minimum_required(VERSION 3.16)

project(Dawn)

add_subdirectory(Dawn)
add_subdirectory(Playground)