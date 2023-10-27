#ifndef LAB02_UTIL_HPP
#define LAB02_UTIL_HPP

#include <vector>
#include <cstdint>
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include "RC6.hpp"

std::vector<uint32_t> stringToUint32Vector(const std::string& str);
bool readBinaryFile(const std::string &filename, std::string& buffer);
bool writeBinaryFile(const std::string &filename, const std::string& data);
std::string uint32VectorToString(const std::vector<uint32_t>& data);
void encryptBMPFile(RC6& rc6, const std::string& filename);
std::vector<uint32_t> readBMPFile(const std::string &filename, std::string& buffer);
double getDistribution(std::vector<uint32_t>& data);
double countCorell(std::vector<uint32_t>& plain, std::vector<uint32_t>& cipher);
std::vector<uint32_t> generateRandomKey();
std::vector<uint32_t> generateRandomIV();

#endif
