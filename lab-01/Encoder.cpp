//
// Created by Александр Ковель on 17.09.2023.
//

#include <string>
#include "Encoder.h"

Encoder::Encoder(uint8_t alphabet_size, std::string new_alphabet) : size_alpha{alphabet_size} {
    for (int i = 0; i < size_alpha; i++) {
        alphabet.push_back(new_alphabet[i]);
    }
}


uint8_t Encoder::encode(uint8_t symbol) {
    for (int i = 0; i < size_alpha; ++i) {
        if (alphabet[i] == symbol) {
            return i;
        }
    }
    throw std::overflow_error("No symbol in encoder");
}

uint8_t Encoder::decode(uint8_t code) {
    if (code >= size_alpha) {
        throw std::overflow_error("No symbol in decoder");
    }
    return alphabet[code];
}
