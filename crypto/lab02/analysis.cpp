#include "analysis.hpp"

void autocorrelationTest(const std::vector<uint32_t>& sequence) {
    int n = sequence.size();
    std::vector<double> autocorrelation(n, 0.0);

    for (int lag = 1; lag < n; ++lag) {
        autocorrelation[lag] = 0.0;
        for (int i = 0; i < n - lag; ++i) {
            autocorrelation[lag] += (sequence[i] & 1) == (sequence[i + lag] & 1) ? 1 : -1;
        }
        autocorrelation[lag] /= n - lag;
    }

    std::cout << "Автокорреляционный тест:" << std::endl;
    for (int lag = 1; lag < n; ++lag) {
        std::cout << "Смещение " << lag << ": " << autocorrelation[lag] << std::endl;
    }
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
