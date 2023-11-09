#include "analysis.hpp"

int calculateA(const std::vector<uint32_t>& sequence, size_t d) {
    size_t n = sequence.size();
    int result = 0;

    for (size_t i = 0; i < n - d; ++i) {
        result += __builtin_popcount(sequence[i] ^ sequence[i + d]);
    }

    return result;
}

double autocorrelationTest(const std::vector<uint32_t>& sequence) {
    size_t n = sequence.size();

    double sum = 0.0;
    for (size_t d = 1; d <= n / 2; ++d) {
        int A_d = calculateA(sequence, d);
        double X5 = 2.0 * (A_d - (n - d)) / std::sqrt(n - d);

        sum += X5;
    }
    return sum / (n/2);
}

int countSerials(const std::vector<uint32_t>& sequence, size_t serialLength) {
    size_t n = sequence.size() * 32;
    int count = 0;

    for (size_t i = 0; i < n - serialLength + 1; ++i) {
        uint32_t currentBits = sequence[i / 32] >> (i % 32);
        uint32_t mask = (1 << serialLength) - 1;

        if ((currentBits & mask) == (currentBits << (32 - serialLength) & mask)) {
            ++count;
            i += serialLength - 1;
        }
    }

    return count;
}
double serialTest(const std::vector<uint32_t>& sequence) {
    size_t n = sequence.size() * 32;
    size_t k = 0;

    while ((n - k + 3) >= (1 << (k + 2))) {
        ++k;
    }

    std::vector<double> ei(k, 0.0);
    for (size_t i = 1; i <= k; ++i) {
        ei[i - 1] = static_cast<double>(n - i + 3) / static_cast<double>(1 << (i + 2));
    }

    std::vector<int> Bi(k, 0);
    std::vector<int> Gi(k, 0);

    for (size_t i = 1; i <= k; ++i) {
        Bi[i - 1] = countSerials(sequence, i);
        Gi[i - 1] = n - Bi[i - 1];
    }

    double X4 = 0.0;

    for (size_t i = 0; i < k; ++i) {
        X4 += std::pow(Bi[i] - ei[i], 2) / ei[i];
        X4 += std::pow(Gi[i] - ei[i], 2) / ei[i];
    }

    return X4;
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

std::vector<int> analyzeBitFrequency(const std::vector<uint32_t>& sequence1, const std::vector<uint32_t>& sequence2) {
    size_t n = sequence1.size() * 32;
    std::vector<int> bitFrequency(n, 0);

    for (size_t i = 0; i < sequence1.size(); ++i) {
        uint32_t xorResult = sequence1[i] ^ sequence2[i];
        for (int j = 0; j < 32; ++j) {
            bitFrequency[i * 32 + j] += (xorResult >> j) & 1;
        }
    }

    return bitFrequency;
}
