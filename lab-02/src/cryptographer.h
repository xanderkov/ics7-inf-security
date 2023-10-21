#ifndef Cryptographer_h
#define Cryptographer_h

#include <iostream>
#include <vector>
#include <algorithm>
#include "utils.h"

class Cryptographer {
private:
    std::vector<int> initialPermutationIP = {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
    };

    std::vector<int> finalPermutationIP = {
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25
    };

    std::vector<int> applyInitialPermutationIP(const std::vector<int>& message) {
        std::vector<int> permutatedMessage;
        for (int i : initialPermutationIP) {
            permutatedMessage.push_back(message[i - 1]);
        }
        return permutatedMessage;
    }

    std::vector<int> applyFinalPermutationIP(const std::vector<int>& message) {
        std::vector<int> permutatedMessage;
        for (int i : finalPermutationIP) {
            permutatedMessage.push_back(message[i - 1]);
        }
        return permutatedMessage;
    }

public:
    std::vector<int> encipher(const std::vector<std::vector<int>>& keys, const std::vector<int>& message, int direction) {
        std::vector<int> permutatedMessage = applyInitialPermutationIP(message);
        std::vector<int> L(permutatedMessage.begin(), permutatedMessage.begin() + 32);
        std::vector<int> R(permutatedMessage.begin() + 32, permutatedMessage.end());

        if (direction == ENCIPHER) {
            for (int i = 0; i < 16; i++) {
                std::vector<int> right_copy = R;
                R = xorForTwoLists(L, FeistelCipher().apply(keys[i], R));
                L = right_copy;
            }
        } else {
            for (int i = 15; i >= 0; i--) {
                std::vector<int> left_copy = L;
                L = xorForTwoLists(R, FeistelCipher().apply(keys[i], L));
                R = left_copy;
            }
        }

        std::vector<int> joinedMessage = L;
        joinedMessage.insert(joinedMessage.end(), R.begin(), R.end());
        std::vector<int> permutatedJoinedMessage = applyFinalPermutationIP(joinedMessage);

        return permutatedJoinedMessage;
    }
};

#endif /* Cryptographer_h */
