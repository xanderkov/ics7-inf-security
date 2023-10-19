//
// Created by Александр Ковель on 12.10.2023.
//

#include "Des.h"
#include <valarray>
#include <bitset>


std::vector<std::vector<unsigned> > Des::generate_key(std::vector<unsigned int> key) {
    std::vector<std::vector<unsigned > > ret_key;
    std::vector<unsigned > C = table.permuteC0(key);
    std::vector<unsigned > D = table.permuteD0(key);
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < C.size(); j++) {
            C[j] = C[j] << table.SI[i];
            D[j] = D[j] << table.SI[i];
            auto sumlabmda = [](auto a, auto b){ return a + b; };
            std::vector<unsigned > newKey = table.permuteCP(sumVectors(C, D, sumlabmda));
            ret_key.push_back(newKey);
        }
    }
    return ret_key;
}

std::vector<unsigned> Des::encode(std::vector<unsigned int> bitsArray) {
    return std::vector<unsigned int>();
}

std::vector<unsigned> Des::decode(std::vector<unsigned int> bitsArray) {
    return std::vector<unsigned int>();
}


std::vector<unsigned> Des::funcFeistel(std::vector<unsigned int> bitsArray, std::vector<unsigned int> key) {
    std::vector<unsigned > E = table.permuteCP(bitsArray);
    std::bitset<48> e_bit, key_bit;
    int t = 0;
    std::for_each(E.begin() + 20, E.begin() + 57, [&](uint8_t val) { e_bit[i] = val; ++t; });
    t = 0;
    std::for_each(key.begin() + 20, key.begin() + 57, [&](uint8_t val) { key_bit[i] = val; ++t; });
    std::bitset<48> Z = e_bit ^ key_bit;

    std::vector<unsigned > sBl;
    std::bitset<32> sBlocks;

    for (int k = 0; k < 8; k++) {
        std::bitset<6> bits = Z >> (k * 6);
        bits &= 0x3F;
        std::bitset<2> iBits = bits[0] << 1 | bits[5];
        std::bitset<4> jBits = bits >> 1;
        unsigned i = iBits.to_ullong();
        unsigned j = jBits.to_ullong();
        unsigned sbl = table.permuteSBlock(k, i * 16 + j);
        std::bitset<32> sBlockBits(sbl);
        sBlocks |= (sBlockBits << (28 - k * 4));
    }
}


