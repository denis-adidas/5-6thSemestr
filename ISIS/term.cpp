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
double Polynomial::errorDecoder(int k, int n, int d, double p) {

    std::vector<int> code_words(32, 0);

    int sum = 0;
    std::vector<int> tmp;
    for (int i = 0; i < static_cast<int>(std::pow(2, k)); i++) {
        tmp = decToBin(i, k);

        for (int j = 0; j < tmp.size(); j++) {
            sum += tmp[j];
        }
        code_words[sum]++;
        sum = 0;
    }


    double result = 0;
    for (int i = d; i < n; i++) {
        result += code_words[i] * std::pow(p, i) * std::pow((1 - p), n - i);
    }


    return result;
}
