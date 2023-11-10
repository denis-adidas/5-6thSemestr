#include "Util.hpp"
#include "RC6.hpp"
#include "analysis.hpp"

std::vector<uint32_t> invertFirstBits(const std::vector<uint32_t>& block) {
    int wordSize = RC6::getWordSize();
    std::vector<uint32_t> temp = block;
    for (int i = 0; i < block.size(); ++i) {
        temp[i] ^= (0xFFFFFFFF << (wordSize / 2));
    }
    return block;
}
std::vector<uint32_t> invertSecondBits(const std::vector<uint32_t>& block) {
    int wordSize = RC6::getWordSize();;
    std::vector<uint32_t> temp = block;
    for (int i = 0; i < block.size(); ++i) {
        temp[i] ^= (0xFFFFFFFF >> (wordSize / 2));
    }
    return block;
}

std::vector<uint32_t> stringToUint32Vector(const std::string& str) {
    std::vector<uint32_t> result;
    const char* data = str.c_str();
    size_t length = str.length();

    for (size_t i = 0; i < length; i += 4) {
        uint32_t value = 0;
        for (int j = 0; j < 4; j++) {
            if (i + j < length) {
                value = (value << 8) | static_cast<uint8_t>(data[i + j]);
            }
        }
        result.push_back(value);
    }

    return result;
}
bool readBinaryFile(const std::string &filename, std::string& buffer) {
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
std::string uint32VectorToString(const std::vector<uint32_t>& data) {
    std::string result;
    for (uint32_t value : data) {
        for (int i = 3; i >= 0; i--) {
            result.push_back(static_cast<char>((value >> (i * 8)) & 0xFF));
        }

    }
    return result;
}

void encryptBMPFile(RC6& rc6, const std::string& filename ) {
    std::string imageData;
    readBinaryFile(filename, imageData);

    std::string pixelData = imageData.substr(54);
    std::vector<uint32_t> pixelUint32Data = stringToUint32Vector(pixelData);

    std::vector<uint32_t> iv = generateRandomIV();
    //lab3 begins here
    //Invert
    std::vector<uint32_t> firstBlocksInvert = invertFirstBits(pixelUint32Data);
    std::vector<uint32_t> secondBlocksInvert = invertSecondBits(pixelUint32Data);

    std::vector<uint32_t> cipherTextFirst = rc6.encryptCBC(iv, firstBlocksInvert);
    std::vector<uint32_t> cipherTextSecond = rc6.encryptCBC(iv, secondBlocksInvert);

    std::cout << "First data auto corellation test: " << autocorrelationTest(firstBlocksInvert) << std::endl;
    std::cout << "Second data auto corellation test: " << autocorrelationTest(secondBlocksInvert) << std::endl;

    std::cout << "First serial test: " << serialTest(firstBlocksInvert) << std::endl;
    std::cout << "Second serial test: " << serialTest(secondBlocksInvert) << std::endl;

    //first frequency test
    frequencyTest(firstBlocksInvert);
    //second frequency test
    frequencyTest(secondBlocksInvert);

    std::vector<int> analyzfrequency;
    analyzfrequency = analyzeBitFrequency(firstBlocksInvert, secondBlocksInvert);

    //end lab3

    std::vector<uint32_t> ciphertext = rc6.encryptCBC(iv, pixelUint32Data);
    std::string encryptedPixelData = uint32VectorToString(ciphertext);
    writeBinaryFile("../data/image_encrypt.bmp", imageData.substr(0, 54) + encryptedPixelData );

    ciphertext[20] = 0x00000000;

    std::vector<uint32_t> decryptedtext = rc6.decryptCBC(iv, ciphertext);
    std::string decryptedPixelData = uint32VectorToString(decryptedtext);
    writeBinaryFile("../data/image_out.bmp",  imageData.substr(0, 54) + decryptedPixelData);

    std::cout << getDistribution(ciphertext) << std::endl;
    std::cout << countCorell(ciphertext, decryptedtext) << std::endl;
}

std::vector<uint32_t> generateRandomKey() {
    std::vector<uint32_t> key;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dist;

    for (int i = 0; i < 4; i++) {
        key.push_back(dist(gen));
    }

    return key;
}
std::vector<uint32_t> generateRandomIV() {
    std::vector<uint32_t> iv;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dist;

    for (int i = 0; i < 4; i++) {
        iv.push_back(dist(gen));
    }

    return iv;
}

double getDistribution(std::vector<uint32_t>& data) {
    int N = 32 * data.size();
    int count = 0;

    for (int i = 0; i < data.size(); i++) {
        uint32_t buffer = data[i];

        for (int j = 0; j < 32; j++) {
            uint32_t b = (buffer >> j) & 1;
            count += b;
        }
    }

    return (double)count / N;
}
void encryptTXTFile(RC6& rc6, const std::string&  filename) {
    std::vector<uint32_t> iv = generateRandomIV();

    std::string inputText;
    readBinaryFile("../data/input.txt", inputText);

    std::vector<uint32_t> plaintext = stringToUint32Vector(inputText);

    std::vector<uint32_t> ciphertext = rc6.encryptCBC(iv, plaintext);
    writeBinaryFile("../data/text_encryp.txt", uint32VectorToString(ciphertext));

    std::vector<uint32_t> decryptedText = rc6.decryptCBC(iv, ciphertext);
    writeBinaryFile("../data/output.txt", uint32VectorToString(decryptedText));

    std::cout << "Text's analysis: " << std::endl;
    std::cout << getDistribution(ciphertext) << std::endl;
    std::cout << countCorell(ciphertext, decryptedText) << std::endl;

}
double countCorell(std::vector<uint32_t>& plain, std::vector<uint32_t>& cipher) {
    int N = 32 * cipher.size();
    int corell = 0;

    if (plain.size() < cipher.size()) {
        return -1.0;
    }

    for (int i = 0; i < cipher.size(); i++) {
        uint32_t p = plain[i];
        uint32_t c = cipher[i];

        for (int j = 0; j < 32; j++) {
            uint32_t tmpP = (p >> j) & 1;
            uint32_t tmpC = (c >> j) & 1;
            corell += (2 * tmpP - 1) * (2 * tmpC - 1);
        }
    }

    return (double)corell / N;
}


