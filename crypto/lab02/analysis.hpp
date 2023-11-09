#ifndef LAB02_ANALYSIS_HPP
#define LAB02_ANALYSIS_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>

double autoCorrelationTest(const std::vector<uint32_t>& sequence1, const std::vector<uint32_t>& sequence2);
void runLengthTest(const std::vector<uint32_t>& sequence);
void frequencyTest(const std::vector<uint32_t>& sequence);


#endif
