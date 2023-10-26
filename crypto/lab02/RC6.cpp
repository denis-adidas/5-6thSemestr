#include "RC6.hpp"

RC6::RC6(const std::vector<uint32_t>& key) {
    keyShedule(key);
}
std::vector<uint32_t> RC6::encrypt(const std::vector<uint32_t>& plaintext) {
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
std::vector<uint32_t> RC6::decrypt(const std::vector<uint32_t>& ciphertext) {
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
std::vector<uint32_t> RC6::encryptCBC(const std::vector<uint32_t>& iv, const std::vector<uint32_t >& plaintext) {
    std::vector<uint32_t> plaintext_temp = plaintext;
    std::vector<uint32_t> ciphertext;
    std::vector<uint32_t> previousBlock = iv;

    for (size_t i = 0; i < plaintext_temp.size(); i += 4) {
        for (int j = 0; j < 4; j++) {
            plaintext_temp[i + j] ^= previousBlock[j];
        }

        std::vector<uint32_t> encryptedBlock = encrypt(plaintext_temp);
        ciphertext.insert(ciphertext.end(), encryptedBlock.begin(), encryptedBlock.end());
        previousBlock = encryptedBlock;
    }

    return ciphertext;
}
std::vector<uint32_t> RC6::decryptCBC(const std::vector<uint32_t>& iv, const std::vector<uint32_t>& ciphertext) {
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
void RC6::keyShedule(const std::vector<uint32_t>& key) {
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
uint32_t RC6::rightRotate(uint32_t value, int shift) {
    return (value >> shift) | (value << (wordSize - shift));
}
uint32_t RC6::leftRotate(uint32_t value, int shift) {
    return (value << shift) | (value >> (wordSize - shift));
}