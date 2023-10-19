#ifndef helpers_h
#define helpers_h

#define ENCIPHER 1
#define DECIPHER -1

std::vector<int> xorForTwoLists(const std::vector<int>& a1, const std::vector<int>& a2) {
    std::vector<int> result;
    for (size_t i = 0; i < a1.size() && i < a2.size(); i++) {
        result.push_back(a1[i] ^ a2[i]);
    }
    return result;
}


#endif /* helpers_h */
