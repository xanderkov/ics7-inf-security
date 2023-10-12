//
// Created by Александр Ковель on 11.10.2023.
//

#include <iostream>
#include <string>
#include <fstream>
#include "PCBC.h"

#define NUM_BLOCKS 16

int init_input(std::string &key, std::string &vector_init, std::string &message) {
    std::ifstream myfile("input.txt");
    std::string line;
    int ret = 0;
    if (myfile.is_open()) {
        if (getline(myfile, line)) {
            std::cout << "Key: " << line << std::endl;
            key = line;
        }
        else {
            ret = -1;
        }
        if (getline(myfile, line)) {
            std::cout << "Vector initialization: " << line << std::endl;
            vector_init = line;
        }
        else {
            ret = -1;
        }
        if (getline(myfile, line)) {
            std::cout << "Message: " << line << std::endl;
            message = line;
        }
        else {
            ret = -1;
        }
        myfile.close();
    }
    else {
        ret = -1;
    }
    return ret;
}

std::vector<std::string> split_message_by_blocks(std::string &message) {
    std::vector<std::string> blocks;
    unsigned long len = std::ceil(message.length() / (float)NUM_BLOCKS);
    for (int i = 0; i < len; i++) {
        unsigned long n = message.length();
        if ((i + 1) * NUM_BLOCKS < message.length()) {
            n = (i + 1) * NUM_BLOCKS;
        }
        blocks.push_back(message.substr(i * NUM_BLOCKS, n - i * NUM_BLOCKS));
    }
    while (blocks.back().length() < NUM_BLOCKS) {
        blocks.back().push_back(' ');
    }
    return blocks;
}

void cast_vector_to_num_blocks(std::string &vector_init) {
    while (vector_init.length() < NUM_BLOCKS) {
        vector_init.push_back(' ');
    }
    vector_init.substr(1, NUM_BLOCKS);
}

int main() {
    std::string key, vector_init, message;
    int ret = init_input(key, vector_init, message);
    std::vector<std::string> blocks = split_message_by_blocks(message);
    cast_vector_to_num_blocks(vector_init);
    PCBC pcbc;
    auto encoded_list = pcbc.encrypt(blocks, key, vector_init);
    std::cout << "Encoded: ";
    for (auto encoded: encoded_list) {
        std::cout << encoded;
    }
    std::cout << std::endl;
    return ret;
}