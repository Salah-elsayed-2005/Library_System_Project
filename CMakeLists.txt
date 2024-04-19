cmake_minimum_required(VERSION 3.24)
project(Library_System_Project)

set(CMAKE_CXX_STANDARD 17)

add_executable(Library_System_Project main.cpp str.h str.cpp Book.cpp Book.h Loan.cpp Loan.h User.h User.cpp
        Date.h Date.cpp)
