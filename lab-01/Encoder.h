//
// Created by Александр Ковель on 17.09.2023.
//

#ifndef LAB_01_ENCODER_H
#define LAB_01_ENCODER_H


#include <cstdint>
#include <vector>

class Encoder {

public:
    Encoder(uint8_t alphabet_size);

    void set_alphabet(std::string new_alphabet);
    uint8_t encode(uint8_t symbol);
    uint8_t decode(uint8_t code);
private:
    uint8_t size_alpha;
    std::vector<uint8_t> alphabet;
};


#endif //LAB_01_ENCODER_H
