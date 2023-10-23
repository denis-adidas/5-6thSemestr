#ifndef LAB02_CIPHER_HPP
#define LAB02_CIPHER_HPP

#include <string>
#include <cstdint>
#include <math.h>

class Cipher {
private:
    uint32_t w, r, b, log_w;
    uint64_t modulo;
    std::string mode, text, key;
    uint32_t* S;
    uint32_t* L;
    static int leftRotate(uint32_t n, uint32_t d, uint32_t w);
    static int rightRotate(uint32_t n, uint32_t d, uint32_t w);
public:
    void keyExpansion(std::string key);
    std::string hex_to_string(unsigned int A, unsigned int B, unsigned int C, unsigned int D);
    Cipher(uint32_t W = 32, uint32_t R = 20, uint32_t B = 16);
    void rd_const(const uint32_t &w, uint32_t& p, uint32_t &q);
    std::string encrypt(const std::string& );
    std::string decrypt(const std::string&);
    ~Cipher();
};

#endif //LAB02_CIPHER_HPP
