#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>

class RC6 {
public:
    RC6(const std::vector<uint32_t>& key) {
        initialize(key);
    }

    std::vector<uint32_t> encrypt(const std::vector<uint32_t>& plaintext) {
        std::vector<uint32_t> ciphertext;
        uint32_t A = 0, B = 0, C = 0, D = 0;

        A = plaintext[0];
        B = plaintext[1];
        C = plaintext[2];
        D = plaintext[3];

        B += S[0];
        D += S[1];

        for (int round = 1; round <= rounds; ++round) {
            uint32_t t = leftRotate((B * (2 * B + 1)), log2w);
            uint32_t u = leftRotate((D * (2 * D + 1)), log2w);

            A = leftRotate((A ^ t), u) + S[2 * round];
            C = leftRotate((C ^ u), t) + S[2 * round + 1];

            uint32_t temp = A;
            A = B;
            B = C;
            C = D;
            D = temp;
        }

        A += S[2 * rounds + 2];
        C += S[2 * rounds + 3];

        ciphertext.push_back(A);
        ciphertext.push_back(B);
        ciphertext.push_back(C);
        ciphertext.push_back(D);

        return ciphertext;
    }

    std::vector<uint32_t> decrypt(const std::vector<uint32_t>& ciphertext) {
        std::vector<uint32_t> plaintext;
        uint32_t A = 0, B = 0, C = 0, D = 0;
        A = ciphertext[0];
        B = ciphertext[1];
        C = ciphertext[2];
        D = ciphertext[3];

        C -= S[2 * rounds + 3];
        A -= S[2 * rounds + 2];

        for (int round = rounds; round >= 1; --round) {
            uint32_t temp = D;
            D = C;
            C = B;
            B = A;
            A = temp;

            uint32_t t = leftRotate(B * (2 * B + 1), log2w);
            uint32_t u = leftRotate(D * (2 * D + 1), log2w);

            C = rightRotate(C - S[2 * round + 1], t) ^ u;
            A = rightRotate(A - S[2 * round], u) ^ t;
        }

        D -= S[1];
        B -= S[0];

        plaintext.push_back(A);
        plaintext.push_back(B);
        plaintext.push_back(C);
        plaintext.push_back(D);

        return plaintext;
    }

    std::vector<uint32_t> encryptCBC(const std::vector<uint32_t>& iv, const std::vector<uint32_t >& plaintext) {
        std::vector<uint32_t> plaintext_temp = plaintext;
        std::vector<uint32_t> ciphertext;
        std::vector<uint32_t> previousBlock = iv;

        for (size_t i = 0; i < plaintext_temp.size(); i += 4) {
            // XOR текущего блока с предыдущим
            for (int j = 0; j < 4; j++) {
                plaintext_temp[i + j] ^= previousBlock[j];
            }

            // Зашифрование текущего блока
            std::vector<uint32_t> encryptedBlock = encrypt(plaintext_temp);

                    // Сохранение зашифрованного блока
                    ciphertext.insert(ciphertext.end(), encryptedBlock.begin(), encryptedBlock.end());

            // Обновление предыдущего блока
            previousBlock = encryptedBlock;
        }

        return ciphertext;
    }

    std::vector<uint32_t> decryptCBC(const std::vector<uint32_t>& iv, const std::vector<uint32_t>& ciphertext) {
        std::vector<uint32_t> plaintextBlocks;
        std::vector<uint32_t> previousBlock = iv;

        for (size_t i = 0; i < ciphertext.size(); i += 4) {

            std::vector<uint32_t> decryptedBlock = decrypt(ciphertext);

            for (int j = 0; j < 4; j++) {
                decryptedBlock[j] ^= previousBlock[j];
            }

            plaintextBlocks.insert(plaintextBlocks.end(), decryptedBlock.begin(), decryptedBlock.end());
            
            previousBlock = ciphertext;
        }

        return plaintextBlocks;
    }

private:
    static const int rounds = 20;
    static const int wordSize = 32;
    static const int log2w = 5;
    std::vector<uint32_t> S;
    std::vector<uint32_t> L;

    uint32_t leftRotate(uint32_t value, int shift) {
        return (value << shift) | (value >> (wordSize - shift));
    }

    uint32_t rightRotate(uint32_t value, int shift) {
        return (value >> shift) | (value << (wordSize - shift));
    }

    void initialize(const std::vector<uint32_t>& key) {
        const int c = key.size();
        const int t = 3 * std::max(c, 2 * rounds + 4);

        S.resize(2 * (rounds + 2));
        L.resize(c);

        for (int i = 0; i < c; ++i) {
            L[i] = key[i];
        }

        uint32_t p = 0xb7e15163;  // Pw, a constant
        S[0] = p;

        uint32_t q = 0x9e3779b9;  // Qw, another constant
        for (int i = 1; i < 2 * rounds + 3; ++i) {
            S[i] = S[i - 1] + q;
        }

        int A = 0, B = 0;
        int i = 0, j = 0;

        for (int v = 0; v < t; ++v) {
            A = S[i] = leftRotate(S[i] + A + B, 3);
            B = L[j] = leftRotate(L[j] + A + B, A + B);
            i = (i + 1) % (2 * rounds + 4);
            j = (j + 1) % c;
        }
    }

};




int main() {

    std::vector<uint32_t> key = {0x12345678, 0x23456789, 0x3456789A, 0x456789AB};
    std::vector<uint32_t> iv = {0xA5A5A5A5, 0x5A5A5A5A, 0xA5A5A5A5, 0x5A5A5A5A};
    RC6 rc6(key);

    std::vector<uint32_t> plaintext = {0x48656C6C, 0x6F20776F, 0x726C64, 0x726C64};
    std::vector<uint32_t> ciphertext = rc6.encryptCBC(iv, plaintext);
    std::vector<uint32_t> decryptedText = rc6.decryptCBC(iv, ciphertext);

    std::cout << "Plaintext: ";
    for (const uint32_t& word : plaintext) {
        std::cout << std::hex << word << " ";
    }
    std::cout << std::endl;

    std::cout << "Ciphertext: ";
    for (const uint32_t& word : ciphertext) {
        std::cout << std::hex << word << " ";
    }
    std::cout << std::endl;

    std::cout << "Decrypted Text: ";
    for (const uint32_t& word : decryptedText) {
        std::cout << std::hex << word << " ";
    }
    std::cout << std::endl;

    return 0;
}
