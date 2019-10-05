cmake_minimum_required(VERSION 3.14)
project(abstractVM)

set(CMAKE_CXX_STANDARD 11)

add_executable(abstractVM src/main.cpp
        src/Operand.hpp src/Operand.cpp src/Factory.cpp src/Factory.hpp)