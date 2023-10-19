cmake_minimum_required(VERSION 3.26)
project(lab_02)

set(CMAKE_C_STANDARD 17)

include_directories(.)

add_executable(lab_02
        main.cpp
        PCBC.cpp
        Des.cpp
        Tables.cpp)
