#include <iostream>
#include <random>
#include "Encoder.h"
#include "Enigma.h"
#include <fstream>
#include <string>
#define ALPHABET_NUM 26

int main() {
    uint8_t num_rotors = 3;

    // Setting up Encoder
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz";
    Encoder encoder(alphabet.size(), alphabet);
    int alphabet_size = alphabet.size();
    // ------------------------

    // Reflectors
    int reflector_number = rand() % alphabet_size;

    std::vector<uint8_t> reflector;
    std::cout << "Reflector number: " << reflector_number << std::endl;
    for (int i = 0; i < alphabet_size; i++) {
        reflector.push_back((reflector_number + alphabet_size - i) % alphabet_size);
        std::cout << static_cast<int>(reflector[i]) << ", ";
    }
    std::cout << std::endl;
    // -----

    // Commutator
    int commutator_number = rand() % alphabet_size;

    std::vector<uint8_t> commutator;
    std::cout << "Commuator number: " << commutator_number << std::endl;
    for (int i = 0; i < alphabet_size; i++) {
        commutator.push_back((commutator_number + i) % alphabet_size);
        std::cout << static_cast<int>(commutator[i]) << ", ";
    }
    std::cout << std::endl;
    // -----

    // Rotors
    std::vector<std::vector<uint8_t>> rotors;
    for (int i = 0; i < num_rotors; i++) {
        int rotor_number = rand() % alphabet_size;
        std::cout << "Rotor number: " << rotor_number << std::endl;
        std::vector<uint8_t> rotor;
        for (int j = 0; j < alphabet_size; ++j) {
            rotor.push_back((rotor_number + j) % alphabet_size);
            std::cout << static_cast<int>(rotor[j]) << ", ";
        }
        rotors.push_back(rotor);
        std::cout << std::endl;
    }
    // --------------------

    // Setting up Enigma machine

    // -------------------------



    // Starting Enigma machine
    std::string message;
//    std::cout << "Input string (without symbols that doesn't used in alphabet): ";
//    std::cin >> message;

    std::string line;
    std::ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            std::vector<uint8_t> new_message;
            std::cout << "Message: " << line << std::endl;
            message = line;
            std::cout << "Encrypted message: ";
            Enigma enigma(alphabet_size, num_rotors, reflector, rotors, commutator);

            for (auto &symbol: message) {
                try {
                    uint8_t encoded_ch = encoder.encode(symbol);
                    encoded_ch = enigma.encrypt(encoded_ch);
                    uint8_t decoded_ch = encoder.decode(encoded_ch);
                    new_message.push_back(decoded_ch);
                    std::cout << decoded_ch;
                } catch (std::overflow_error &e) {
                    std::cout << e.what() << std::endl;
                }

            }

            std::cout << std::endl;
            std::cout << "Decrypted message: ";
            // Check Enigma work
            Enigma enigma_two(alphabet_size, num_rotors, reflector, rotors, commutator);
            for (auto &symbol: new_message) {
                try {
                    uint8_t encoded_ch = encoder.encode(symbol);
                    encoded_ch = enigma_two.encrypt(encoded_ch);
                    uint8_t decoded_ch = encoder.decode(encoded_ch);
                    std::cout << decoded_ch;
                } catch (std::overflow_error &e) {
                    std::cout << e.what() << std::endl;
                }

            }
            std::cout << std::endl;

    }
        myfile.close();

    }
    return 0;
}