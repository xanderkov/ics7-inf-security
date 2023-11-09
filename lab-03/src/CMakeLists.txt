cmake_minimum_required(VERSION 3.26)
project(lab_03)

set(CMAKE_CXX_STANDARD 20)
include_directories(.)

add_executable(lab_03 main.cpp
        mixColumns.cpp
        PolyOptn.cpp
        Sbox.cpp
        shiftRows.cpp
        keyEnpy.cpp
        main.cpp
        keyExpansion.cpp
)
