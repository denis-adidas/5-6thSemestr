#ifndef BINARY_SYMMETRIC_CHANNEL_UTILS_H
#define BINARY_SYMMETRIC_CHANNEL_UTILS_H

#include <vector>
#include <iostream>
#include <random>
#include <map>

#include "system.h"
#include "Utils.h"

template<typename CharT>
class DecimalSeparator : public std::numpunct<CharT>
{
public:
    DecimalSeparator(CharT Separator)
            : m_Separator(Separator)
    {}

protected:
    CharT do_decimal_point()const
    {
        return m_Separator;
    }

private:
    CharT m_Separator;
};

std::vector<bool> genRandomErrors(int size, double p){
    if ((p < 0.0) || (p > 1.001)){
        std::cerr << "genRandomErrors(): p != [0; 1]" << std::endl;
        exit(-1);
    }
    // Генератор для e - генератор случайного вектора ошибок
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    std::vector<bool> res;
    for (int i = 0; i < size; i++){
        res.push_back(dis(gen) < p);
    }
    return res;
}

std::vector<bool> genErrors(int size, bool value){
    std::vector<bool> res;
    for (int i = 0; i < size; i++){
        res.push_back(value);
    }
    return res;
}

std::vector<bool> genRandomMessage(int size){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 1);

    std::vector<bool> res;
    for (int i = 0; i < size; i++){
        res.push_back(dis(gen) == 1);
    }
    return res;
}

int w(const std::vector<bool>& a){
    int count = 0;
    for (int i = 0; i < a.size(); i++) if (a[i]) count++;
    return count;
}

std::ostream& operator<<(std::ostream& os, const std::vector<bool>& a) {
    for (int i = a.size() - 1; i >= 0; --i) {
        os << (a[i] ? '1' : '0');
    }
    return os;
}

int degreeVec(const std::vector<bool>& a) {
    if (a.empty()) return -1; // Обработка пустого вектора
    for (size_t i = a.size() - 1; i != static_cast<size_t>(-1); --i) {
        if (a[i])
            return static_cast<int>(i);
    }
    return -1;
}

void clearZeros(std::vector<bool>& a) {
    while (!a.empty() && !a.back())
        a.pop_back();
    if (a.empty()) a.push_back(false);
}

std::vector<bool> mod(const std::vector<bool>& a, const std::vector<bool>& b) {
    std::vector<bool> remainder = a;

    while (!remainder.empty() && degreeVec(remainder) >= degreeVec(b)) {
        int shift = degreeVec(remainder) - degreeVec(b);

        for (size_t i = 0; i < b.size(); ++i) {
            if (i + shift < remainder.size())
                remainder[i + shift] = remainder[i + shift] ^ b[i];
        }
    }
    clearZeros(remainder);

    return remainder;
}

void modChecker(){
    std::vector<bool> a({0, 0, 0, 1, 1, 1, 1}); // 120
    std::vector<bool> b({0, 0, 0, 1, 1, 1, 0}); // 56
    std::vector<bool> res = mod(a, b); // 8
    std::cout << "120 mod 56 = 8" << std::endl;
    std::cout << a << " mod " << b << " = " << res << std::endl << std::endl;

    std::vector<bool> a1({0, 1, 1, 0, 0, 0, 1}); // 70
    std::vector<bool> b1({0, 0, 0, 0, 1, 0, 1}); // 80
    std::vector<bool> res1 = mod(a1, b1); // 70
    std::cout << "70 mod 80 = 70 (why 22?)" << std::endl;
    std::cout << a1 << " mod " << b1 << " = " << res1 << std::endl << std::endl;

    std::vector<bool> a2({0, 1, 1, 0, 0, 0, 1}); // 70
    std::vector<bool> b2({0, 1, 1, 0, 0, 0, 1}); // 70
    std::vector<bool> res2 = mod(a2, b2); // 70
    std::cout << "70 mod 70 = 0" << std::endl;
    std::cout << a2 << " mod " << b2 << " = " << res2 << std::endl << std::endl;

    a.clear();
    b.clear();
    res.clear();

    a1.clear();
    b1.clear();
    res1.clear();

    a2.clear();
    b2.clear();
    res2.clear();
}

void checkStatement2(const std::map<std::vector<bool>, std::vector<bool>>& codeBook){
    for (auto i: codeBook){
        for (auto j: codeBook){
            std::vector<bool> res;
            for (int k = 0; k < i.second.size(); k++){
                res.push_back(i.second[k] ^ j.second[k]);
            }
            bool check = true;
            for (auto k: codeBook){
                if (k.second == res){
                    check = false;
                    break;
                }
            }
            if (check){
                std::cout << "checkStatement2 error: " << i.second << " ^ " << j.second << " isn't codeBook part." << std::endl;
            }
        }
    }
    std::cout << "checkStatement2() finished." << std::endl;
}

void generateVariations(std::vector<bool>& m, int index, std::vector<std::vector<bool>>& variations) {
    if (index == m.size()) {
        variations.push_back(m);
        return;
    }

    m[index] = false;
    generateVariations(m, index + 1, variations);

    m[index] = true;
    generateVariations(m, index + 1, variations);
}

#endif //BINARY_SYMMETRIC_CHANNEL_UTILS_H
