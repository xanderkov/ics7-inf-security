#include <iostream>
#include <vector>
#include <fstream>
#include <vector>
#include <bitset>
#include <random>
#include "feistelCipher.h"
#include "roundKeysGenerator.h"
#include "utils.h"
#include "cryptographer.h"

std::vector<int> initVector = {1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1};

std::pair<std::vector<std::vector<int>>, size_t> fileToMessageBlocks(const std::string& filenameIn) {
    std::ifstream file(filenameIn, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    std::vector<unsigned char> messageBytes(std::istreambuf_iterator<char>(file), {});
    file.close();

    std::string messageBinary;
    for (const auto& byte : messageBytes) {
        messageBinary += std::bitset<8>(byte).to_string();
    }

    std::vector<std::vector<int>> messageBinaryBlocks;
    for (size_t i = 0; i < messageBinary.size() / 64; i++) {
        std::vector<int> block;
        for (size_t j = 0; j < 64; j++) {
            block.push_back(messageBinary[i * 64 + j] - '0');
        }
        messageBinaryBlocks.push_back(block);
    }

    size_t truncateBytesCount = 0;
    if (messageBinary.size() % 64) {
        std::vector<int> lastBlock;
        size_t messageBinarySize = messageBinary.size();
        for (size_t i = 0; i < messageBinarySize % 64; i++) {
            lastBlock.push_back(messageBinary[messageBinarySize - messageBinarySize % 64 + i] - '0');
        }
        truncateBytesCount = (64 - lastBlock.size()) / 8;
        //truncateBytesCount = 0;
        lastBlock.resize(64, 1);
        messageBinaryBlocks.push_back(lastBlock);
    }

    return std::pair(messageBinaryBlocks, truncateBytesCount);
}

void messageBlocksToFile(std::string filenameOut, std::vector<std::vector<int>> messageBlocks, size_t truncateBytesCount) {
    std::vector<std::string> messageBinary;

    for (int i = 0; i < int(messageBlocks.size()) - 1; i++) {
        for (int j = 0; j < 8; ++j) {
            std::string curStr;
            for (int s = j * 8; s < messageBlocks[i].size() && s < (j + 1) * 8; s++) {
                curStr += std::to_string(messageBlocks[i][s]);
            }
            messageBinary.push_back(curStr);
        }
    }

    if (!messageBlocks.empty()){
        for (int j = 0; j < 8 - truncateBytesCount; ++j) {
            std::string curStr;
            std::vector<int> block = messageBlocks.back();
            for (int s = j * 8; s < block.size() && s < (j + 1) * 8; s++) {
                curStr += std::to_string(block[s]);
            }
            messageBinary.push_back(curStr);
        }
    }

    std::vector<int> messageOrd;
    for (const auto& x : messageBinary) {
        messageOrd.push_back(std::stoi(x, 0, 2));
    }

    std::vector<unsigned char> messageBytes;
    for (const auto& x : messageOrd) {
        messageBytes.push_back(static_cast<unsigned char>(x));
    }

    std::ofstream f_out(filenameOut, std::ios::binary);
    for (const auto& x : messageBytes) {
        f_out.write(reinterpret_cast<const char*>(&x), 1);
    }
    f_out.close();
}

size_t encipherFile(std::vector<std::vector<int>> keys,
                    const std::string &filenameIn, const std::string &filenameOut, int direction, size_t truncateBytesCount) {
    auto res = fileToMessageBlocks(filenameIn);
    std::vector<std::vector<int>> messageBlocks = res.first;

    Cryptographer cryptographer;

    std::vector<std::vector<int>> encipheredBlocks;
    size_t messageBlocksSize = messageBlocks.size();
    auto initVectorCopy = initVector;
    for (size_t i = 0; i < messageBlocksSize; i++) {
        if (direction == ENCIPHER) {
            auto decoded_block = xorForTwoLists(initVectorCopy, messageBlocks[i]);
            auto encode = cryptographer.encipher(keys, decoded_block, direction);
            encipheredBlocks.push_back(encode);
            initVectorCopy = xorForTwoLists(encode, messageBlocks[i]);
        }
        else {
            auto decode = cryptographer.encipher(keys, messageBlocks[i], direction);
            decode = xorForTwoLists(initVectorCopy, decode);
            initVectorCopy = xorForTwoLists(decode, messageBlocks[i]);
            encipheredBlocks.push_back(decode);
        }

    }

    if (direction == DECIPHER) {
        messageBlocksToFile(filenameOut, encipheredBlocks, truncateBytesCount);
    } else {
        messageBlocksToFile(filenameOut, encipheredBlocks, 0);
    }

    return res.second;
}

int main() {
    std::vector<int> key = {1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1};
    std::vector<std::vector<int>> keys = RoundKeysGenerator().generate(key);

    std::string inputFile = "input/medic.jpg";
    std::string outputFileEnciphered = "output/enciphered.jpg";
    std::string outputFileDeciphered = "output/deciphered.jpg";

    auto truncateBytesCount = encipherFile(keys, inputFile, outputFileEnciphered, ENCIPHER, 0);
    encipherFile(keys, outputFileEnciphered, outputFileDeciphered, DECIPHER, truncateBytesCount);

    return 0;
}
