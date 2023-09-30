//
// Created by Александр Ковель on 17.09.2023.
//

#include "Enigma.h"
#include <iostream>

Enigma::Enigma(uint8_t size_rotor,
               uint8_t num_rotors,
               const std::vector<uint8_t>& reflector_place,
               const std::vector<std::vector<uint8_t>>& rotors_place,
               const std::vector<uint8_t>& commutator_place) :
    size_rotor{size_rotor}, num_rotors{num_rotors} {

    reflector.reserve(size_rotor);
    for (const auto &reflect: reflector_place) {
        reflector.push_back(reflect);
    }
    for (const auto &rotor: rotors_place) {
        rotors.push_back(rotor);
    }
    for (const auto &comm: commutator_place) {
        commutator.push_back(comm);
    }
}


uint8_t Enigma::find_rotor(uint8_t num, uint8_t code) {
    for (int i = 0; i < size_rotor; ++i) {
        if (rotors[num][i] == code) {
            return i;
        }
    }
    throw std::out_of_range("Code doesn't founded");
}

void Enigma::rotor_shift(uint8_t num) {
    uint8_t temp = rotors[num][size_rotor - 1];
    for (int i = size_rotor - 1; i > 0; --i) {
        rotors[num][i] = rotors[num][i - 1];
    }
    rotors[num][0] = temp;
}

uint8_t Enigma::encrypt(uint8_t code) {
    uint64_t rotor_queue = 1;
    uint8_t new_code = code;

    if (code > size_rotor) {
        throw std::out_of_range("Code bigger than size of rotor");
    }
    new_code = commutator[new_code];

    for (auto &rotor: rotors) {
        new_code = rotor[new_code];
    }
    new_code = reflector[new_code];

    for (int i = num_rotors - 1; i >= 0; --i) {
        try {
            new_code = find_rotor(i, new_code);
        }
        catch (const std::overflow_error& e) {
            std::cout << e.what() << std::endl;
        }
    }

    counter++;
    for (int i = 0; i < num_rotors; ++i) {
        if (counter % rotor_queue == 0) {
            rotor_shift(i);
        }
        rotor_queue *= size_rotor;
    }
    new_code = commutator[new_code];

    return new_code;
}



