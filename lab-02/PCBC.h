//
// Created by Александр Ковель on 12.10.2023.
//

#ifndef LAB_02_PCBC_H
#define LAB_02_PCBC_H

#include "Des.h"

class PCBC {
public:
    std::vector<std::string> encrypt(std::vector<std::string> blocks, std::string key, std::string vector_init);
    std::string blocks_xor(std::string left, std::string right);
};


#endif //LAB_02_PCBC_H
