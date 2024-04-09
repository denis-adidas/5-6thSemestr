
#ifndef TERM_HPP
#define TERM_HPP

#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

class Polynomial {
private:
    std::vector<int> coefficients;
public:
    Polynomial() = default;

    explicit Polynomial(const std::vector<int>& coeffs) : coefficients(coeffs) {}
    explicit Polynomial(int a) {
        for (int i = 0; i <= a-1; i++) {
            coefficients.emplace_back(0);
        }
        coefficients.emplace_back(1);
    }


    void inputPolynomial() {
        int degree;
        std::cout << "Enter the degree of the polynomial: ";
        std::cin >> degree;

        coefficients.resize(degree + 1);

        std::cout << "Enter the coefficients of the polynomial, starting from the constant term: ";
        for (int i = degree; i >= 0; --i) {
            std::cout << "Coefficient of x^" << i << ": ";
            std::cin >> coefficients[i];
        }
    }

    void outputPolynomial() const {
        int degree = coefficients.size() - 1;

        for (int i = degree; i >= 0; --i) {
            if (coefficients[i] != 0) {
                if (i < degree) {
                    std::cout << " + ";
                }
                std::cout << coefficients[i];
                if (i > 0) {
                    std::cout << "x";
                    if (i > 1) {
                        std::cout << "^" << i;
                    }
                }
            }
        }
        std::cout << std::endl;
    }

    Polynomial operator+(const Polynomial& other) const {
        Polynomial result;
        int size = std::max(coefficients.size(), other.coefficients.size());
        result.coefficients.resize(size);

        for (int i = 0; i < size; ++i) {
            int coef1 = (i < coefficients.size()) ? coefficients[i] : 0;
            int coef2 = (i < other.coefficients.size()) ? other.coefficients[i] : 0;
            result.coefficients[i] = coef1 ^ coef2;
        }

        return result;
    }
    Polynomial operator*(const Polynomial& other) const {
        Polynomial result;
        result.coefficients.resize(coefficients.size() + other.coefficients.size() - 1);

        for (int i = 0; i < coefficients.size(); ++i) {
            for (int j = 0; j < other.coefficients.size(); ++j) {
                result.coefficients[i + j] ^= coefficients[i] & other.coefficients[j];
            }
        }
        // std::reverse(result.coefficients.begin(), result.coefficients.end());
        return result;
    }

public:
    static double upperEstimate(int dist, int length, double probability);
    static double errorDecoder(const std::vector<int>& g, int k, int n, int d, double& p);
    [[nodiscard]] Polynomial remainderGF2(const Polynomial& devider) const;
    [[nodiscard]] std::vector<int> encoder(const std::vector<int>& g) const;

    [[nodiscard]] int degree() const {
        int ind = static_cast<int>(coefficients.size() - 1);
        auto tmp = coefficients;
        std::reverse(tmp.begin(), tmp.end());
        for (auto it : tmp) {
            if (it == 1)
                break;
            ind--;
        }
        return ind;
    }

    std::vector<int> getData() {
        return coefficients;
    }
};


#endif