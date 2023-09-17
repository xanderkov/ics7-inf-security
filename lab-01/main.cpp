#include <iostream>
#include <random>
#include "Encoder.h"
#include "Enigma.h"
#define ALPHABET_NUM 26

int main() {
    uint8_t num_rotors = 3;

    // Reflectors
    int reflector_number = rand() % ALPHABET_NUM;
    std::cout << "Reflector number: " << reflector_number << std::endl;
    std::vector<uint8_t> reflector;
//    = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < ALPHABET_NUM; i++) {
        reflector.push_back((reflector_number + i) % ALPHABET_NUM);
        std::cout << static_cast<int>(reflector[i]) << ", ";
    }
    std::cout << std::endl;
    // -----

    // Rotors
    std::vector<std::vector<uint8_t>> rotors;
//    =
//            {
//                    {17, 18, 19, 20, 21, 22, 23, 24, 25, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
//                    {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0, 1, 2, 3, 4},
//                    {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
//            };
    rotors.reserve(num_rotors);
    for (int i = 0; i < num_rotors; i++) {
        int rotor_number = rand() % ALPHABET_NUM;
        std::cout << "Rotor number: " << rotor_number << std::endl;
        rotors[i].reserve(ALPHABET_NUM);
        for (int j = 0; j < ALPHABET_NUM; ++j) {
            rotors[i][j] = (rotor_number + j) % ALPHABET_NUM;
            std::cout << static_cast<int>(rotors[i][j]) << ", ";
        }
        std::cout << std::endl;
    }
    // --------------------

    // Setting up Enigma machine
    Enigma enigma(ALPHABET_NUM, num_rotors);
    enigma.set_reflector(reflector);
    for (int i = 0; i < num_rotors; i++) {
        enigma.set_rotor(i, rotors[i]);
    }
    // -------------------------

    // Setting up Encoder
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    uint8_t size_alpha = alphabet.size();
    Encoder encoder(size_alpha);
    encoder.set_alphabet(alphabet);
    // ------------------------

    // Starting Enigma machine
    std::string message;
    std::cout << "Input string (without symbols that doesn't used in alphabet): ";
    std::cin >> message;

    for (auto &symbol: message) {
        try {
            uint8_t encoded_ch = encoder.encode(symbol);
            encoded_ch = enigma.encrypt(encoded_ch);
            uint8_t decoded_ch = encoder.decode(encoded_ch);
            std::cout << decoded_ch;

        } catch (std::overflow_error &e) {
            std::cout << e.what() << std::endl;
        }

    }
    return 0;
}