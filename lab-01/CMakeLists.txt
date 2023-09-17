cmake_minimum_required(VERSION 3.26)
project(lab_01)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab_01
        main.cpp
        Enigma.cpp
        Enigma.h
        Encoder.cpp
        Encoder.h)
