#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;


vector<int> coder(vector<int> m, vector<int> g);

// ������ ����� ��� ���������
unsigned long long factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}


unsigned long long combinations(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        std:: cout << "Uncorrect!" << endl;
        return 1;
    }
    return factorial(n) / (factorial(k) * factorial(n - k));
}
// ����� ����� ��� ������ � �����������


// ���� ��� ������ �� ��������� (������)
double power(double base, int exponent) {
    if (exponent == 0) {
        return 1; 
    }
    else if (exponent > 0) {
        double result = 1;
        for (int i = 0; i < exponent; ++i) {
            result *= base;
        }
        return result;
    }
    else {
       
        base = 1 / base;
        exponent = -exponent;
        double result = 1;
        for (int i = 0; i < exponent; ++i) {
            result *= base;
        }
        return result;
    }
}
// ���� ��� ������ �� ��������� (�����)



// ���� ��� ���������� ������� ������ ������ ������������� (������)
double upper_estimate (int dist, int length, double probability) {
    double right = 0;
    for (int i = 0; i < dist; i++) {
        right += combinations(length, i) * power(probability, i) * power((1 - probability), (length - i));
    }
    return (1 - right);
}
// ���� ��� ���������� ������� ������ ������ ������������� (�����)




// ���� ��� �������� ����������� ����� � �������� (������)
vector<int> decimalToBinary(int decimal, int length) {
    vector<int> binary;
    int remainder = 0;

    if (decimal == 0) {
        for (int i = 0; i < length; i++) {
            binary.push_back(0);
        }
        return binary;
    }

    while (decimal > 0) {
        remainder = decimal % 2;
        binary.push_back(remainder);
        decimal /= 2;
    }
    if (binary.size() < length) {
        while (binary.size() != length) {
            binary.push_back(0);
        }
    }
    reverse(binary.begin(), binary.end());
    return binary;
}
// ���� ��� �������� ����������� ����� � �������� (�����)


// ���� ��� ���������� ������� �������� ����������� ������ ������������� (������)
double decodeErr(vector<int> g, int k, int n, int d, double p) {
    int chek = (int)power(2, k);
    vector<int> code_words(32, 0);
    
  

    int sum = 0;
    vector<int> tmp;

    for (int i = 0; i < chek; i++) {
        tmp = decimalToBinary(i, k);
        tmp = coder(tmp, g);
        for (int j = 0; j < tmp.size(); j++) {
            sum += tmp[j];
        }
        code_words[sum]++;
        tmp.clear();
        sum = 0;
    }


    double result = 0;
    for (int i = d; i < n; i++) {
        result += code_words[i] * power(p, i) * power((1 - p), (n - i));
    }
   
   
    return result;
}
// ���� ��� ���������� ������� �������� ����������� ������ ������������� (�����)


// ���� ��� ������ � ������������ (������)



vector<int> multiplyPolynomials(vector<int> a, vector<int> b) {
    if (a[0] == 0) {
        int ch = 0;
        for (auto it : a) {
            if (it == 1)
                break;
            ch++;
        }
        a.erase(a.begin(), (a.begin() + ch));
    }
    if (b[0] == 0) {
        int ch = 0;
        for (auto it : b) {
            if (it == 1)
                break;
            ch++;
        }
        b.erase(b.begin(), (b.begin() + ch));
    }
    
    int n = a.size();
    int m = b.size();
    vector<int> result(n + m - 1, 0); 

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result[i + j] ^= a[i] & b[j]; 
        }
    }

    return result;
}

int deg(vector<int> a) {
    int ind = a.size() - 1;
    for (auto it : a) {
        if (it == 1)
            break;
        ind--;
    }
    return ind;
}

vector<int> makePolynom(int a) {
    vector<int> b;
    for (int i = 0; i <= a; i++) {
        b.push_back(0);
    }
    b[0] = 1;
    return b;
}

vector<int> polynomial_remainder_GF2(vector<int> a, vector<int> b) {
    vector<int> remainder = a;
    int m = a.size();
    int n = b.size();
    if (n < m) {
        while (n != m) {
            b.insert(b.begin(), 0);
            n++;
        }
    }
    vector <int> tmp1, tmp2;

    while (deg(remainder) >= deg(b)) {
        tmp1 = makePolynom(deg(remainder) - deg(b));
        tmp2 = multiplyPolynomials(tmp1, b);
        if (tmp2.size() != remainder.size()) {
            while (tmp2.size() != remainder.size()) {
                tmp2.insert(tmp2.begin(), 0);
            }
        }
        for (int i = 0; i < a.size(); i++) {
            remainder[i] = tmp2[i] ^ remainder[i];
        }
    }

    int chek = 0;
    if (remainder[0] == 0) {
        for (auto it : remainder) {
            if (it == 1)
                break;
            chek++;
        }
        for (int i = 0; i < chek; i++) {
            remainder.erase(remainder.begin());
        }
    }

    return remainder; // ���������� �������
}

vector<int> coder(vector<int> m, vector<int> g) {
    vector<int> c = polynomial_remainder_GF2(multiplyPolynomials(m, makePolynom(deg(g))), g); // c(x)
    vector<int> a = multiplyPolynomials(m, makePolynom(deg(g))); // m(x)*x^r

    for (auto it : c) {
        std::cout << it << ' ';
    }

    if (c.size() != a.size()) {
        while (c.size() != a.size()) {
            c.insert(c.begin(), 0);
        }
    }
    for (int i = 0; i < a.size(); i++) { // a(x)
        a[i] = a[i] ^ c[i];
    }
    if (a.size() != (m.size() + deg(g))) { // n = k + r
        while (a.size() != (m.size() + deg(g))) {
            a.insert(a.begin(), 0);
        }
    }
    return a;
}

//���� ��� ������ � ������������ (�����)

int main() { 
   

srand(time(NULL));

vector<int> g = {0, 0, 0, 1, 1}; // x^3 + x + 1

// vector<int> g = {1, 0, 0, 0, 1};
//  vector<int> in = {1, 0, 1, 1};

    // auto test = coder(in, g);
    // auto c = polynomial_remainder_GF2(g, in);

    // for (auto it : c) {
    //     std::cout << it << ' ';
    // }

 double up_est = 0;
 double err_dec = 0;

 int d = 0;
 int k = 0;
 double p = 0;
 int r = deg(g);
 int l = 0;

 int n = k + r;

 up_est = upper_estimate(d, k, p);
 err_dec = decodeErr(g, k, n, d, p);



 for (int i = 0; i < 100; i++) {
     k = (rand() % 10) + 2;
     d = (rand() % 5) + 1;
     p = (double)((rand() % 100) + 1)/100;


      l = k - 1;
      n = l + r;
      if (d > n) {
          while (n != d + 2) {
              n++;
          }
      }
      up_est = upper_estimate(d, n, p);
      err_dec = decodeErr(g, l, n, d, p);
      std::cout << up_est << " " << err_dec << endl;

      l = k + 1;
      n = l + r;
      if (d > n) {
          while (n != d + 2) {
              n++;
          }
      }
      up_est = upper_estimate(d, n, p);
      err_dec = decodeErr(g, l, n, d, p);
      std::cout << up_est << " " << err_dec << endl;

      l = k;
      n = l + r;
      if (d > n) {
          while (n != d + 2) {
              n++;
          }
      }
      up_est = upper_estimate(d, n, p);
      err_dec = decodeErr(g, l, n, d, p);
      std::cout << up_est << " " << err_dec << endl;

      std::cout << endl;
 }

    
    
 
	return 0;
}