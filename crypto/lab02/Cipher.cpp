#include <iostream>
#include <fstream>

#include "Cipher.hpp"

Cipher::Cipher(uint32_t W, uint32_t R, uint32_t B) {
    w = W;
    r = R;
    b = B;
    log_w = static_cast<uint32_t>(log2(w));
    modulo = std::pow(2, w);
    S = new uint32_t[2 * r + 4];
}
Cipher::~Cipher() {
    delete S;
}
void Cipher::rd_const(const uint32_t &w, uint32_t& p, uint32_t &q) {
    p = (uint32_t)std::ceil(((M_E - 2) * std::pow(2, w)));
    q = (uint32_t)((1.618033988749895 - 1) * std::pow(2, w));
}
 int Cipher::leftRotate(uint32_t n, uint32_t d, uint32_t w) {
        return (n << d) | (n >> (w - d));
}

int Cipher::rightRotate(uint32_t n, uint32_t d, uint32_t w) {
        return (n >> d) | (n << (w - d));
}
//add work with byte in L
void Cipher::keyExpansion(std::string key) {
    const uint32_t w_bytes = std::ceil(static_cast<float> (w / 8));
    const uint32_t c = std::ceil(static_cast<float> (b / 8));

    uint32_t p, q;
    rd_const(w, p, q);

    L = new uint32_t[c];
    for (int i = 0; i < c; ++i) {
        L[i] = 0;
    }
    S[0] = p;
    for (int i = 1; i <= (2*r + 3); ++i) {
        S[i] = (S[i-1] + q) % modulo;
    }

    uint32_t A =0, B = 0, i = 0, j = 0;
    int v = 3 * std::max(c, (2* r + 4));
    for (int s = 1; s <= v; s++) {
        A = S[i] = leftRotate((S[i] + A + B) % modulo, 3, w);
        B = L[j] = leftRotate((L[j] + A + B) % modulo, (A + B), w);
        i = (i + 1) % (2 * r + 4);
        j = (j + 1) % c;
    }
}

std::string Cipher::encrypt(const std::string &input) {
    std::string result;

    uint32_t A, B, C, D;
    for (size_t i = 0; i < input.size(); i += 16) {
        for (int j = 0; j < 4; j++) {
            if (i + j * 4 < input.size()) {
                uint32_t value = *(reinterpret_cast<const uint32_t*>(&input[i + j * 4]));
                if (j == 0) A = value;
                else if (j == 1) B = value;
                else if (j == 2) C = value;
                else if (j == 3) D = value;
            }
        }

        uint32_t t, u, temp;

        B += S[0];
        D += S[1];
        for (int i = 1; i <= r; ++i) {
            t = leftRotate((B * (2 * B + 1)) % modulo, log_w, w);
            u = leftRotate((D * (2 * D + 1)) % modulo, log_w, w);
            A = leftRotate((A ^ t), u, w) + S[2 * i];
            C = leftRotate((C ^ u), t, w) + S[2 * i + 1];
            temp = A;
            A = B;
            B = C;
            C = D;
            D = temp;
        }
        A += S[2 * r + 2];
        C += S[2 * r + 3];

        result += std::string(reinterpret_cast<char*>(&A), 4);
        result += std::string(reinterpret_cast<char*>(&B), 4);
        result += std::string(reinterpret_cast<char*>(&C), 4);
        result += std::string(reinterpret_cast<char*>(&D), 4);
        //add result
    }
    return result;
}

std::string Cipher::decrypt(const std::string &input) {
    std::string result;

    uint32_t A, B, C, D;
    for (size_t i = 0; i < input.size(); i += 16) {
        for (int j = 0; j < 4; j++) {
            if (i + j * 4 < input.size()) {
                uint32_t value = *(reinterpret_cast<const uint32_t*>(&input[i + j * 4]));
                if (j == 0) A = value;
                else if (j == 1) B = value;
                else if (j == 2) C = value;
                else if (j == 3) D = value;
            }
        }

        uint32_t t, u, temp;

        C -= S[2 * r + 3];
        A -= S[2 * r + 2];
        for (int i = r; i >= 1; --i) {
            temp = D;
            D = C;
            C = B;
            B = A;
            A = temp;
            u = leftRotate((D * (2 * D + 1)) % modulo, log_w, w);
            t = leftRotate((B * (2 * B + 1)) % modulo, log_w, w);
            C = rightRotate((C - S[2 * i + 1]) % modulo, t, w) ^ u;
            A = rightRotate((A - S[2 * i]) % modulo, u, w) ^ t;
        }
        D -= S[1];
        B -= S[0];

        result += std::string(reinterpret_cast<char*>(&A), 4);
        result += std::string(reinterpret_cast<char*>(&B), 4);
        result += std::string(reinterpret_cast<char*>(&C), 4);
        result += std::string(reinterpret_cast<char*>(&D), 4);
    }
    return result;
}

bool readBinaryFile(const std::string &filename, std::string& buffer) {
    if(filename.find(".bmp") != std::string::npos) {

    }
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Unable to open file for reading." << std::endl;
        return false;
    }

    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    buffer.resize(static_cast<size_t>(fileSize));
    if (!file.read(reinterpret_cast<char *>(buffer.data()), fileSize)) {
        std::cerr << "Failed to read file." << std::endl;
        return false;
    }

    return true;
}

bool writeBinaryFile(const std::string &filename, const std::string& data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Unable to open file for writing." << std::endl;
        return false;
    }

    if (!file.write(reinterpret_cast<const char *>(data.data()), data.size())) {
        std::cerr << "Failed to write file." << std::endl;
        return false;
    }

    return true;
}