#include "term.hpp"
#include <iostream>
#include <random>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distribution(1, 16);
    std::uniform_real_distribution<double> distribution_p(0.01, 1.0);

    int r = 0;
    int l = 0;

    int k = 0;
    int n = 0;

    int d = 0;
    double p;

    for (int i = 0; i < 100; ++i) {
        r = distribution(gen);
        k = distribution(gen);
        d = distribution(gen);
        p = distribution_p(gen);

        l = --k;
        n = l + r;
        if (d > n) {
            while (n != d + 2) {
                n++;
            }
        }
        std::cout << Polynomial::upperEstimate(d, n, p) << ' ';
        std::cout << Polynomial::errorDecoder(l, n, d, p)  << std::endl;

        l = ++k;
        n = l + r;
        if (d > n) {
            while (n != d + 2) {
                n++;
            }
        }
        std::cout << Polynomial::upperEstimate(d, n, p) << ' ';
        std::cout << Polynomial::errorDecoder(l, n, d, p)  << std::endl;

        l = k;
        n = l + r;
        if (d > n) {
            while (n != d + 2) {
                n++;
            }
        }
        std::cout << Polynomial::upperEstimate(d, n, p) << ' ';
        std::cout << Polynomial::errorDecoder(l, n, d, p)  << std::endl;

        std::cout << std::endl;
    }

    return 0;
}
