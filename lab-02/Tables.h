//
// Created by Александр Ковель on 16.10.2023.
//

#ifndef LAB_02_TABLES_H
#define LAB_02_TABLES_H

#include <vector>
#include <filesystem>
#include <iostream>


class Tables {
public:
    Tables();
    unsigned permuteSBlock(unsigned IndexBlock, unsigned IndexArr);
    std::vector<unsigned > permuteC0(std::vector<unsigned > bitsArray);
    std::vector<unsigned > permuteD0(std::vector<unsigned > bitsArray);
    std::vector<unsigned > permuteSI(std::vector<unsigned > bitsArray);

    std::vector<unsigned > permuteCP(std::vector<unsigned > bitsArray);
    std::vector<unsigned > permuteIP(std::vector<unsigned > bitsArray);
    std::vector<unsigned > permuteIPInverse(std::vector<unsigned > bitsArray);
    std::vector<unsigned > permuteP(std::vector<unsigned > bitsArray);
    std::vector<unsigned > permuteE(std::vector<unsigned > bitsArray);

    std::vector< std::vector<unsigned> > SBlocks;
    std::vector<unsigned int> SI;

private:
    std::vector<unsigned int> C0;
    std::vector<unsigned int> D0;
    std::vector<unsigned int> CP;

    std::vector<unsigned int> IP;
    std::vector<unsigned int> IPInverse;

    std::vector<unsigned int> P;
    std::vector<unsigned int> E;
private:
    std::vector<unsigned> readFileChars(std::string path, unsigned reduce_index = 1);
    std::vector<std::vector<unsigned > > readSBlocks(std::string path);
    std::vector<unsigned > permute(std::vector<unsigned > bitsArray, std::vector<unsigned > indexes);



};


#endif //LAB_02_TABLES_H
