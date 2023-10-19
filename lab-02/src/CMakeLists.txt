cmake_minimum_required(VERSION 3.26)
project(src)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(src
        cryptographer.h
        feistelCipher.h
        utils.h
        main.cpp
        roundKeysGenerator.h)
