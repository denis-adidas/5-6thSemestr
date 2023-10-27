#include "RC6.hpp"
#include "Util.hpp"



int main() {

    std::vector<uint32_t> key = generateRandomKey();
    std::vector<uint32_t> iv = generateRandomIV();
    RC6 rc6(key);

    std::string inputText;

    encryptBMPFile(rc6,R"(D:\CLion_projects\crypto\lab02\data\image.bmp)");


    return 0;
}
