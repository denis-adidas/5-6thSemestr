#include <iostream>
#include <random>

#include "term.hpp"
#include "util.hpp"

void count(const std::vector<int>& base, int& l, int& r, int& d, double& p) {
    int n = l + r;
    if (d > n) {
        while (n != d + 2) {
            n++;
        }
    }
    std::cout << Polynomial::upperEstimate(d, n, p) << ' ';
    std::cout << Polynomial::errorDecoder(base, l, n, d, p)  << std::endl;
}



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

    Polynomial a;
    a.inputPolynomial();

    auto base = a.getData();
    r = a.degree();

    for (int i = 0; i < 100; ++i) {
        k = distribution(gen);
        d = distribution(gen);
        p = distribution_p(gen);

        l = k-1;
        count(base, l, r, d, p);

        l = k+1;
        count(base, l, r, d, p);

        l = k;
        count(base, l, r, d, p);

        std::cout << std::endl;
    }

    return 0;
}
