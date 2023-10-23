#include <iostream>
#include <vector>
#include <cstdint>

const uint32_t P32 = 0xB7E15163; // Magic constants for RC6
const uint32_t Q32 = 0x9E3779B9;
const int rounds = 20; // Number of rounds
const int wordSize = 32; // Size of a word in bits

class RC6 {
public:
    RC6(const std::vector<uint32_t>& key) {
        keySetup(key);
    }

    void keySetup(const std::vector<uint32_t>& key) {
        w.resize(2 * (rounds + 1));
        w[0] = P32;

        for (int i = 1; i < 2 * (rounds + 1); ++i) {
            w[i] = w[i - 1] + Q32;
        }

        std::vector<uint32_t> key_schedule;
        key_schedule.insert(key_schedule.end(), key.begin(), key.end());

        while (key_schedule.size() < 2 * (rounds + 1)) {
            key_schedule.push_back(0);
        }

        uint32_t A = 0;
        uint32_t B = 0;
        int i = 0;
        int j = 0;

        for (int k = 0; k < 3 * std::max(2 * (rounds + 1), static_cast<int>(key_schedule.size())); ++k) {
            A = w[i] = rotate_left((w[i] + A + B), 3);
            B = key_schedule[j] = rotate_left((key_schedule[j] + A + B), (A + B));
            i = (i + 1) % (2 * (rounds + 1));
            j = (j + 1) % key_schedule.size();
        }
    }

    std::vector<uint32_t> encrypt(const std::vector<uint32_t>& plaintext) {
        std::vector<uint32_t> ciphertext;
        for (size_t i = 0; i < plaintext.size(); i += 2) {
            uint32_t A = plaintext[i];
            uint32_t B = plaintext[i + 1];
            A += w[0];
            B += w[1];

            for (int round = 1; round <= rounds; ++round) {
                uint32_t t = rotate_left((A * (2 * A + 1)), lgw);
                uint32_t u = rotate_left((B * (2 * B + 1)), lgw);
                A = rotate_left((A ^ t), u) + w[2 * round];
                B = rotate_left((B ^ u), t) + w[2 * round + 1];
            }

            A += w[2 * rounds + 2];
            B += w[2 * rounds + 3];
            ciphertext.push_back(A);
            ciphertext.push_back(B);
        }
        return ciphertext;
    }

    std::vector<uint32_t> decrypt(const std::vector<uint32_t>& ciphertext) {
        std::vector<uint32_t> plaintext;
        for (size_t i = 0; i < ciphertext.size(); i += 2) {
            uint32_t A = ciphertext[i];
            uint32_t B = ciphertext[i + 1];
            B -= w[2 * rounds + 3];
            A -= w[2 * rounds + 2];

            for (int round = rounds; round >= 1; --round) {
                uint32_t t = rotate_left((A * (2 * A + 1)), lgw);
                uint32_t u = rotate_left((B * (2 * B + 1)), lgw);
                B = rotate_right(B - w[2 * round + 1], t) ^ u;
                A = rotate_right(A - w[2 * round], u) ^ t;
            }

            B -= w[1];
            A -= w[0];
            plaintext.push_back(A);
            plaintext.push_back(B);
        }
        return plaintext;
    }

private:
    const int lgw = 5; // lg(w) - for shifting

    std::vector<uint32_t> w;

    uint32_t rotate_left(uint32_t value, int count) {
        return (value << count) | (value >> (wordSize - count));
    }

    uint32_t rotate_right(uint32_t value, int count) {
        return (value >> count) | (value << (wordSize - count));
    }
};

int main() {
    std::vector<uint32_t> key = {0x00010203, 0x04050607, 0x08090A0B, 0x0C0D0E0F}; // 128-bit key
    std::vector<uint32_t> plaintext = {0x00112233, 0x44556677, 0x8899AABB, 0xCCDDEEFF}; // 128-bit plaintext

    RC6 rc6(key);
    std::vector<uint32_t> ciphertext = rc6.encrypt(plaintext);
    std::vector<uint32_t> decrypted = rc6.decrypt(ciphertext);

    std::cout << "Ciphertext: ";
    for (uint32_t value : ciphertext) {
        std::cout << std::hex << value << " ";
    }
    std::cout << std::endl;

    std::cout << "Decrypted Text: ";
    for (uint32_t value : decrypted) {
        std::cout << std::hex << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
