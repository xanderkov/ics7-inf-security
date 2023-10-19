//
// Created by Александр Ковель on 12.10.2023.
//

#ifndef LAB_02_DES_H
#define LAB_02_DES_H

#include <string>
#include <Tables.h>

class Des {
private:

    Tables table;
    std::vector<std::vector<unsigned >> keys;
public:
    std::vector<std::vector<unsigned> > generate_key(std::vector<unsigned> key);
    std::vector<unsigned> encode(std::vector<unsigned> bitsArray);
    std::vector<unsigned> decode(std::vector<unsigned> bitsArray);
    std::vector<unsigned> funcFeistel(std::vector<unsigned> bitsArray, std::vector<unsigned > key);
private:
    template<class UnaryFunction>
    std::vector<unsigned > sumVectors(std::vector<unsigned> a, std::vector<unsigned> b, UnaryFunction operation) {
        std::vector<unsigned > sumVec;
        for (int k = 0; k < a.size(); k++) {
            sumVec.push_back(operation(a[k], b[k]));
        }
        return sumVec;
    }
};


#endif //LAB_02_DES_H
