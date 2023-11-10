#ifndef LAB02_RC6_HPP
#define LAB02_RC6_HPP

#include <cstdint>
#include <vector>

class RC6 {
public:
    RC6(const std::vector<uint32_t>& key);
    std::vector<uint32_t> encrypt(const std::vector<uint32_t>& plaintext);
    std::vector<uint32_t> decrypt(const std::vector<uint32_t>& ciphertext);

    std::vector<uint32_t> encryptCBC(const std::vector<uint32_t>& iv, const std::vector<uint32_t >& plaintext);
    std::vector<uint32_t> decryptCBC(const std::vector<uint32_t>& iv, const std::vector<uint32_t>& ciphertext);

    void applyPKCS7Padding(std::vector<uint32_t>& data, size_t blockSize);
    bool removePKCS7Padding(std::vector<uint32_t>& data);

    std::vector<uint32_t> encryptData(const std::vector<uint32_t>& data);
    std::vector<uint32_t> decryptData(const std::vector<uint32_t>& ciphertext);

    void invertFirstBits(std::vector<uint32_t>& block);
    void invertSecondBits(std::vector<uint32_t>& block);

    std::vector<uint32_t> encryptDataWithInvert(const std::vector<uint32_t>& data);
    std::vector<uint32_t> decryptDataWithInvert(const std::vector<uint32_t>& ciphertext);

    static int getWordSize() {
        return wordSize;
    }

private:
    static const int rounds = 20;
    static const int wordSize = 32;
    static const int log2w = 5;
    std::vector<uint32_t> S;
    std::vector<uint32_t> L;
    std::vector<uint32_t> text;

    static uint32_t leftRotate(uint32_t value, int shift);
    uint32_t rightRotate(uint32_t value, int shift);
    void keyShedule(const std::vector<uint32_t>& key);
};

#endif //LAB02_RC6_HPP
