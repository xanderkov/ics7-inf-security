//
// Created by Александр Ковель on 12.10.2023.
//

#include "PCBC.h"
#include <iostream>
#include <string>
#include "Des.h"

std::vector<std::string> PCBC::encrypt(std::vector<std::string> blocks, std::string key, std::string vector_init) {
    Des des;
    des.generate_key(key);
    std::string left = vector_init;

    std::vector<std::string> encode_list;
    for (auto block: blocks) {
        std::string decoded_block = blocks_xor(left, block);
        std::string encoded = des.encrypt(decoded_block);
        encode_list.push_back(encoded);
        left = blocks_xor(encoded, block);
    }
    return encode_list;
}

std::string PCBC::blocks_xor(std::string left, std::string right) {
    std::string xor_c;
    std::vector<char> degug;
    for (int i = 0; i < 16; i++) {
        char c1 = left[i];
        char c2 = right[i];
        xor_c.push_back(c1 ^ c2);
        degug.push_back(c1 ^ c2);
    }
    return xor_c;
}
