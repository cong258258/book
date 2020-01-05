cmake_minimum_required(VERSION 3.15)
project(book)

set(CMAKE_CXX_STANDARD 14)

add_executable(book main.cpp book.h cmd.cpp everything.h user_man.cpp)