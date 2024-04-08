//
// Created by den_p on 3/11/2024.
//

#include "term.hpp"
#include "util.hpp"



double Polynomial::upperEstimate(int dist, int length, double probability) {
    double right = 0;
    for (int i = 0; i < dist; i++) {
        right += combinations(length, i) * std::pow(probability, i) * std::pow((1 - probability), (length - i));
    }
    return (1 - right);
}
double Polynomial::errorDecoder(const std::vector<int>& g, int k, int n, int d, double p) {

    std::vector<int> code_words(32, 0);

    int sum = 0;
    for (int i = 0; i < static_cast<int>(std::pow(2, k)); i++) {
        auto tmp = Polynomial(decToBin(i, k));
        auto tmpVec = tmp.encoder(g);
        for (int j : tmpVec) {
            sum += j;
        }

        code_words[sum]++;
        sum = 0;
    }

    double result = 0;
    for (int i = d; i <= n; i++) {
        result += code_words[i] * std::pow(p, i) * std::pow((1 - p), n - i);
    }


    return std::abs(result);
}

Polynomial Polynomial::remainderGF2(const Polynomial& divider) const {
    Polynomial dividend = *this;
    Polynomial result;

    while (dividend.degree() >= divider.degree() && dividend.degree() != -1) {
        int degreeDiff = dividend.degree() - divider.degree();
        std::vector<int> tempCoefficients(degreeDiff + 1, 0);

        tempCoefficients[degreeDiff] = 1;

        Polynomial term(tempCoefficients);
        Polynomial product = divider * term;

        dividend = dividend + product;
    }

    return dividend;
}

std::vector<int> Polynomial::encoder(const std::vector<int>& g) const {
    Polynomial basePol(g);

    Polynomial tmp = *this * Polynomial(basePol.degree());
    Polynomial c = tmp.remainderGF2(basePol);


    Polynomial a = *this * Polynomial(basePol.degree()) + c;


    return a.getData();
}

