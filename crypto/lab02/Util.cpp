#include "Util.hpp"

std::vector<uint32_t> stringToUint32Vector(const std::string& str) {
    std::vector<uint32_t> result;
    if (str.size() % 16 != 0)
        return result;
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