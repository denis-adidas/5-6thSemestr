//
// Created by den_p on 3/11/2024.
//

#include "util.hpp"

uint32_t factorial(int n) {
    if ((n == 0) || (n == 1)) {
        return 1;
    }
    return n * factorial(n - 1);
}

uint32_t combinations(int n, int k) {
    if ((n < 0) || (k < 0) || (k > n)) {
        std::cerr << "Incorrect value for combination";
        return 1;
    }
    return factorial(n) / (factorial(k) * factorial(n-k));
}

std::vector<int> decToBin(int decimalNumber, int length) {
    std::vector<int> binaryRepresentation;

    if (decimalNumber == 0) {
        binaryRepresentation.push_back(0);
    } else {
        while (decimalNumber > 0) {
            binaryRepresentation.insert(binaryRepresentation.begin(), decimalNumber % 2);
            decimalNumber /= 2;
        }
    }
    while (binaryRepresentation.size() < length) {
        binaryRepresentation.insert(binaryRepresentation.begin(), 0);
    }

    return binaryRepresentation;
}
