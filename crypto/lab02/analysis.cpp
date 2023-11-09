#include "analysis.hpp"

double autoCorrelationTest(const std::vector<uint32_t>& sequence1, const std::vector<uint32_t>& sequence2) {

    size_t n = sequence1.size();

    double sum1 = 0.0, sum2 = 0.0, sum3 = 0.0;

    for (size_t i = 0; i < n; ++i) {
        sum1 += sequence1[i];
        sum2 += sequence2[i];
        sum3 += sequence1[i] * sequence2[i];
    }

    double mean1 = sum1 / n;
    double mean2 = sum2 / n;
    double mean3 = sum3 / n;

    double cov = mean3 - mean1 * mean2;
    double stdDev1 = sqrt((sum1 * sum1 - n * mean1 * mean1) / n);
    double stdDev2 = sqrt((sum2 * sum2 - n * mean2 * mean2) / n);

    return cov / (stdDev1 * stdDev2);
}


void runLengthTest(const std::vector<uint32_t>& sequence) {
    int n = sequence.size();
    int runLength = 0;
    std::vector<int> runLengthCounts(n, 0);

    for (int i = 1; i < n; ++i) {
        if ((sequence[i] & 1) == (sequence[i - 1] & 1)) {
            runLength++;
        } else {
            runLengthCounts[runLength]++;
            runLength = 0;
        }
    }

    std::cout << "Тест серий:" << std::endl;
    for (int length = 1; length < n; ++length) {
        std::cout << "Длина серии " << length << ": " << runLengthCounts[length] << std::endl;
    }
}

void frequencyTest(const std::vector<uint32_t>& sequence) {
    int n = sequence.size();
    int countZeros = 0;
    int countOnes = 0;

    for (int i = 0; i < n; ++i) {
        countZeros += (sequence[i] & 1) == 0 ? 1 : 0;
        countOnes += (sequence[i] & 1) == 1 ? 1 : 0;
    }

    double expectedFrequency = 0.5;

    std::cout << "Частотный тест:" << std::endl;
    std::cout << "Частота 0: " << static_cast<double>(countZeros) / n << ", Ожидаемая: " << expectedFrequency << std::endl;
    std::cout << "Частота 1: " << static_cast<double>(countOnes) / n << ", Ожидаемая: " << expectedFrequency << std::endl;
}
