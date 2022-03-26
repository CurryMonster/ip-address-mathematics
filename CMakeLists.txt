cmake_minimum_required(VERSION 3.22.1)
project("IP Address Mathematics")
add_executable(prog main.cpp header.cpp)
target_compile_options(prog PUBLIC -g -Wall -Wextra -Wpedantic -std=c++17)
