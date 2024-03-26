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

int hammingDistance(const std::vector<int>& v1, const std::vector<int>& v2) {
    int distance = 0;

    for (size_t i = 0; i < v1.size(); ++i) {
        if (v1[i] != v2[i]) {
            distance++;
        }
    }
    return distance;
}

int calculateHammingDistances(const std::vector<std::vector<int>>& vectors) {
    std::vector<int> data;
    for (size_t i = 0; i < vectors.size(); ++i) {
        for (size_t j = i + 1; j < vectors.size(); ++j) {
            int distance = hammingDistance(vectors[i], vectors[j]);
            data.emplace_back(distance);
        }
    }
    int res = *std::min_element(data.begin(), data.end());
    return res;
}

int countD(const std::vector<int>& g, int k) {
    std::vector<std::vector<int>> codeWords(static_cast<int>(std::pow(2, k)));

    for (int i = 0; i < static_cast<int>(std::pow(2, k)); i++) {
        auto tmp = Polynomial(decToBin(i, k));
        auto tmpVec = tmp.encoder(g);
        codeWords.emplace_back(tmpVec);
    }
    int res = calculateHammingDistances(codeWords);
    for (auto it : codeWords) {
        for (auto itt : it) {
            std::cout << itt << ' ';
        }
        std::cout << std::endl;
    }

    return res+1;

}

int main() {
    // std::random_device rd;
    // std::mt19937 gen(rd());
    //
    // std::uniform_int_distribution<int> distribution(1, 16);
    // std::uniform_real_distribution<double> distribution_p(0.01, 1.0);

    int r = 0;
    int l = 0;

    int k = 4;
    int n = 0;

    int d = 0;
    double p = 0.01;

    //
    Polynomial a;
    a.inputPolynomial();

    auto base = a.getData();
    r = a.degree();
    //
    d = countD(base, k);
    //
    //
    for (double p = 0.01; p <= 1.01; p+= 0.01) {
    //
    l = k-1;
    count(base, l, r, d, p);
        std::cout << "Probability: " << p << std::endl;
    //
        l = k+1;
        count(base, l, r, d, p);
        std::cout << "Probability: " << p << std::endl;

        l = k;
        count(base, l, r, d, p);
        std::cout << "Probability: " << p << std::endl;

        std::cout << std::endl;
    }

    return 0;
}
