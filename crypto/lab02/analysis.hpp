#ifndef LAB02_ANALYSIS_HPP
#define LAB02_ANALYSIS_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>

double autocorrelationTest(const std::vector<uint32_t>& sequence);
void runLengthTest(const std::vector<uint32_t>& sequence);
void frequencyTest(const std::vector<uint32_t>& sequence);
double serialTest(const std::vector<uint32_t>& sequence);
int countSerials(const std::vector<uint32_t>& sequence, size_t serialLength);

#endif
