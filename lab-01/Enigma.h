//
// Created by Александр Ковель on 17.09.2023.
//

#ifndef LAB_01_ENIGMA_H
#define LAB_01_ENIGMA_H

#include <cinttypes>
#include <cstdio>
#include <memory>
#include <vector>


class Enigma {


public:
    Enigma(uint8_t size_rotor,
           uint8_t num_rotors,
           const std::vector<uint8_t>& reflector_place,
           const std::vector<std::vector<uint8_t>>& rotors_place,
           const std::vector<uint8_t>& commutator_place);

    uint8_t encrypt(uint8_t code);

private:
    uint8_t find_rotor(uint8_t num, uint8_t code);
    void rotor_shift(uint8_t num);
private:
    uint64_t counter = 0;
    uint8_t size_rotor;
    uint8_t num_rotors;
    std::vector<uint8_t> reflector;
    std::vector<uint8_t> commutator;
    std::vector<std::vector<uint8_t>> rotors;
};


#endif //LAB_01_ENIGMA_H
