cmake_minimum_required(VERSION 3.24)
project(Library_System_Project)

set(CMAKE_CXX_STANDARD 17)

add_executable(Library_System_Project main.cpp
        str.h
        Book.h
        Loan.h
        User.h
        DatabaseManager.h
        str.cpp
        Book.cpp
        Loan.cpp
        User.cpp
        DatabaseManager.cpp
)

find_package (SQLite3)
if (SQLITE3_FOUND)
    include_directories(${SQLITE3_INCLUDE_DIRS})
    target_link_libraries (Library_System_Project SQLite::SQLite3)
endif (SQLITE3_FOUND)
