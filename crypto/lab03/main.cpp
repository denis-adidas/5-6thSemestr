#include "RC6.hpp"
#include "Util.hpp"



int main() {

    std::vector<uint32_t> key = generateRandomKey();
    std::vector<uint32_t> iv = generateRandomIV();
    RC6 rc6(key);

    std::string inputText;

    encryptBMPFile(rc6,"../data/image.bmp");
//    encryptTXTFile(rc6, "../data/input.txt");



    return 0;
}























//
//
//
//readBinaryFile(R"(D:\CLion_projects\crypto\lab02\data\input.txt)", inputText);
//
//
//std::vector<uint32_t> plaintext = stringToUint32Vector(inputText);
//
//if (plaintext.empty())
//std::cout << "errorrrr" << std::endl;
//
//std::vector<uint32_t> ciphertext = rc6.encryptCBC(iv, plaintext);
//std::vector<uint32_t> decryptedText = rc6.decryptCBC(iv, ciphertext);
//
//
//std::cout << "Plaintext: ";
//for (const uint32_t& word : plaintext) {
//std::cout << std::hex << word << " ";
//}
//std::cout << std::endl;
//std::cout << "Ciphertext: ";
//for (const uint32_t& word : ciphertext) {
//std::cout << std::hex << word << " ";
//}
//std::cout << std::endl;
//std::cout << "Decrypted Text: ";
//for (const uint32_t& word : decryptedText) {
//std::cout << std::hex << word << " ";
//}
//std::cout << std::endl;
//std::cout << "Decrypted Text2: " << uint32VectorToString(decryptedText) << std::endl;
//
//writeBinaryFile(R"(D:\CLion_projects\crypto\lab02\data\output.txt)", uint32VectorToString(decryptedText));