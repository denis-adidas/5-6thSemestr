#include <iostream>
#include <set>
#include <cmath>
#include <string>

typedef struct {
    int maxFrequency;
    int minFrequency;
    char minChar;
    char maxChar;
} frequency;

std::string CaesarCipherEncoder(const std::string& inputString, int offset) {
    std::string encryptedString = inputString;
    for (auto it = encryptedString.begin(); it != encryptedString.end(); ++it) {
        if (isalpha(*it) && isupper(*it)) {
            *it += offset;
            if (static_cast<int>(*it) > 90)
                *it -= 26;
        }
        else if (isalpha(*it)) {
            *it += offset;
            if (static_cast<int>(*it) > 122)
                *it -= 26;
        }
        else if (isdigit(*it)){
            *it += offset;
            if (static_cast<int>(*it) > 57)
                *it -= 10;
        }
    }

    return encryptedString;
}
std::string CaesarCipherDecoder(const std::string& inputString, int offset) {
    std::string encryptedString = inputString;
    for (auto it = encryptedString.begin(); it != encryptedString.end(); ++it) {
        if (isalpha(*it) && isupper(*it)) {
            *it -= offset;
            if (static_cast<int>(*it) < 65)
                *it += 26;
        }
        else if (isalpha(*it)) {
            *it -= offset;
            if (static_cast<int>(*it) < 96)
                *it += 26;
        }
        else if (isdigit(*it)){
            *it -= offset;
            if (static_cast<int>(*it) < 48)
                *it += 10;
        }
    }

    return encryptedString;
}
frequency frequencyAnalysis(const std::string& inputString) {
    std::multiset<char> symbols;
    frequency maxMin;
    for (auto it = inputString.begin(); it != inputString.end(); ++it) {
        symbols.insert(*it);
    }
    int max = 0, min = inputString.length();
    for (auto it = symbols.begin(); it != symbols.end(); ++it) {
        if (symbols.count(*it) > max) {
            max = symbols.count(*it);
            maxMin.maxChar = *it;
            maxMin.maxFrequency = max;
        }
        if (symbols.count(*it) < min) {
            min = symbols.count(*it);
            maxMin.minChar = *it;
            maxMin.minFrequency = min;
        }
    }
    return maxMin;
}

double uniqueness(const std::string& inputString) {
    std::multiset<char> symbols;
    double sum = 0;
    for (auto it = inputString.begin(); it != inputString.end(); ++it) {
        symbols.insert(*it);
    }
    for (auto it = symbols.begin(); it != symbols.end(); ++it) {
        sum += std::pow(static_cast<double>(symbols.count(*it)) / inputString.length(), 2);

    }
    return sum;
}

int main() {
    int offset = 0;
    std::string str;
    std::cout << "Enter the string: " << std::endl;
    std::getline(std::cin >> std::ws, str);
    std::cout << "Enter the offset: " << std::endl;
    std::cin >> offset;

    std::string encode = CaesarCipherEncoder(str, offset);
    std::string decode = CaesarCipherDecoder(encode, offset);
    frequency temp = frequencyAnalysis(encode);

    std::cout << "Your encode string: " << encode << std::endl;
    std::cout << "Your decode string: " << decode << std::endl;
    std::cout << "Frequency analysis: \nMax frequency: " << temp.maxChar << ", Count: " << temp.maxFrequency << ';' << std::endl;
    std::cout << "Min frequency: " << temp.minChar << ", Count: " << temp.minFrequency << ';' << std::endl;
    std::cout << "Uniqueness: " << uniqueness(encode) << ';' << std::endl;

    return 0;
}

//sdfsdfsdfjsioduf12344532