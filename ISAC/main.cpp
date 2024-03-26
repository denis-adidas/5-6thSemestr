#include <iostream>
#include <vector>
#include <fstream>
#include <thread>

#include "system.h"
#include "theory.h"

std::string path = "C:\\2\\";

void makeGraph(int l, const std::vector<bool>& g, int DCount, double eps, const std::string& fileName){
    std::cout << "\n\nStating generating " << path << fileName << std::endl;
    /// Вывод кодовой книги
    auto codeBook = createCodeBook(g, l);
    std::cout << "Code book:" << std::endl;
    for (auto i: codeBook){
        std::cout << i.second << " = " << w(i.second) << std::endl;
    }

    /// Мин. раст. кода
    int d = 10000;
    for (auto c: codeBook){
        for (auto b: codeBook){
            if (c == b) continue;
            int dtmp = 0;
            for (int h = 0; h < c.second.size(); h++){
                if (c.second[h] != b.second[h]) dtmp++;
            }
            if (dtmp < d) d = dtmp;
        }
    }
    std::cout << "d = " << d << " - min. code length" << std::endl;
    if (DCount == 0) DCount = d;

    /// График теоретической ошибки
    std::vector<double> theoryGraph;
    double delta = 0.01;
    for (double p = 0.0; p <= 1.001; p += delta){
        double theoryValue = theory(codeBook, codeBook.begin()->second.size(), p, DCount);
        theoryGraph.emplace_back(theoryValue);
    }

    /// Вывод графика
    std::ofstream file(path + fileName);
    if (!file.is_open()){
        std::cerr << "File hasn't opened!" << std::endl;
        exit(-1);
    }

    /// График экспериментальной ошибки
    int it = 0;
    for (double p = 0.0; p <= 1.001; p += delta){
        int Nerr = 0;
        double iterations = 9 / (4 * eps * eps);
        for (int i = 0; i < iterations; i++){
            auto m = genRandomMessage(l);
            auto a = coder(m, g, false);
            auto e = genRandomErrors(a.size(), p);
            auto b = secondChannel(a, e, false);
            int scount = w(decoder(b, g, false));
            int ecount = w(e);
            if ((scount == 0) && (ecount != 0)) Nerr++;

            m.clear();
            a.clear();
            e.clear();
            b.clear();
        }
        file << p << "=" << theoryGraph[it] << "=" << Nerr/iterations << "=" << iterations << std::endl;
        it++;
    }
    file.close();
    std::cout << path + fileName + " created" << std::endl;

    theoryGraph.clear();
}

int main() {
    path = "C:\\2\\OTS\\";
    makeGraph(3, {1, 1, 1, 0, 1}, 4, 0.1, "second,l-3,eps0.1.txt");
    makeGraph(3, {1, 1, 1, 0, 1}, 4, 0.01, "second,l-3,eps0.01.txt");
}
