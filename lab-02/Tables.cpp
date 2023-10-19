//
// Created by Александр Ковель on 16.10.2023.
//

#include <fstream>
#include "Tables.h"

#define KEYS_FOLDER      " ./data/keys/"
#define ENCODER_FOLDER   "./data/encoder/"
#define FEISTEL_FOLDER   "./data/feistel/"
#define S_BLOCKS_FOLDER  "./data/feistel/sBlocks/"

std::vector<unsigned> Tables::readFileChars(std::string path, unsigned int reduce_index) {
    std::ifstream myfile(path.c_str());
    std::string line;
    std::vector<unsigned> ret;
    if (myfile.is_open()) {
        while (getline(myfile, line, ' ')) {
            ret.push_back(std::atoi(line.c_str()) + reduce_index);
        }
    }
    return ret;
}

Tables::Tables() {
    C0 = readFileChars(std::string(KEYS_FOLDER) + "C0.txt");
    D0 = readFileChars(std::string(KEYS_FOLDER) + "D0.txt");
    SI = readFileChars(std::string(KEYS_FOLDER) + "SI.txt");
    CP = readFileChars(std::string(KEYS_FOLDER) + "CP.txt");

    IP = readFileChars(std::string(ENCODER_FOLDER) + "IP.txt");
    IPInverse = readFileChars(std::string(ENCODER_FOLDER) + "IPInverse.txt");

    E = readFileChars(std::string(FEISTEL_FOLDER) + "E.txt");
    P = readFileChars(std::string(FEISTEL_FOLDER) + "P.txt");

    SBlocks = readSBlocks(S_BLOCKS_FOLDER);
}

std::vector<std::vector<unsigned> > Tables::readSBlocks(std::string path) {
    std::vector< std::vector<unsigned> > Blocks;
    for (int i = 1; i < 9; ++i) {
        Blocks.push_back(readFileChars(path + char(i) + ".txt", 0));
    }
    return Blocks;
}

std::vector<unsigned> Tables::permute(std::vector<unsigned int> bitsArray, std::vector<unsigned int> indexes) {
    std::vector<unsigned > newBitsArray;
    for (auto index: indexes) {
        newBitsArray.push_back(bitsArray[index]);
    }
    return newBitsArray;
}

    unsigned Tables::permuteSBlock(unsigned int IndexBlock, unsigned int IndexArr) {
        return SBlocks[IndexBlock][IndexArr];
    }

std::vector<unsigned> Tables::permuteC0(std::vector<unsigned int> bitsArray) {
    return permute(bitsArray, C0);
}

std::vector<unsigned> Tables::permuteD0(std::vector<unsigned int> bitsArray) {
    return permute(bitsArray, D0);
}

std::vector<unsigned> Tables::permuteSI(std::vector<unsigned int> bitsArray) {
    return permute(bitsArray, SI);
}

std::vector<unsigned> Tables::permuteCP(std::vector<unsigned int> bitsArray) {
    return permute(bitsArray, CP);
}

std::vector<unsigned> Tables::permuteIP(std::vector<unsigned int> bitsArray) {
    return permute(bitsArray, IP);
}

std::vector<unsigned> Tables::permuteIPInverse(std::vector<unsigned int> bitsArray) {
    return permute(bitsArray, IPInverse);
}

std::vector<unsigned> Tables::permuteP(std::vector<unsigned int> bitsArray) {
    return permute(bitsArray, P);
}

std::vector<unsigned> Tables::permuteE(std::vector<unsigned int> bitsArray) {
    return permute(bitsArray, E);
}
