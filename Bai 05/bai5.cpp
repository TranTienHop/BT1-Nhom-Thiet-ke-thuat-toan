#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
#include <limits>
#include <string>
using namespace std;

using cd = complex<double>;
const double PI = acos(-1.0);

void fft(vector<cd>& a, bool invert) {
    int n = (int)a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j];
                cd v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd& x : a) x /= n;
    }
}

vector<long long> multiplyFFT(const vector<long long>& a, const vector<long long>& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < (int)a.size() + (int)b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);

    vector<long long> result(n);
    for (int i = 0; i < n; i++) {
        result[i] = (long long)llround(fa[i].real());
    }
    while (result.size() > 1 && result.back() == 0) result.pop_back();
    return result;
}

vector<long long> multiplyKaratsuba(vector<long long> a, vector<long long> b) {
    int n = (int)max(a.size(), b.size());
    if (n <= 32) {
        vector<long long> res(a.size() + b.size() - 1, 0);
        for (size_t i = 0; i < a.size(); i++)
            for (size_t j = 0; j < b.size(); j++)
                res[i + j] += a[i] * b[j];
        return res;
    }

    while ((int)a.size() < n) a.push_back(0);
    while ((int)b.size() < n) b.push_back(0);
    if (n & 1) {
        a.push_back(0);
        b.push_back(0);
        n++;
    }

    int k = n / 2;
    vector<long long> a0(a.begin(), a.begin() + k);
    vector<long long> a1(a.begin() + k, a.end());
    vector<long long> b0(b.begin(), b.begin() + k);
    vector<long long> b1(b.begin() + k, b.end());

    auto z0 = multiplyKaratsuba(a0, b0);
    auto z2 = multiplyKaratsuba(a1, b1);

    vector<long long> a0a1(k), b0b1(k);
    for (int i = 0; i < k; i++) {
        a0a1[i] = a0[i] + a1[i];
        b0b1[i] = b0[i] + b1[i];
    }
    auto z1 = multiplyKaratsuba(a0a1, b0b1);
    for (size_t i = 0; i < z1.size(); i++) {
        long long v0 = (i < z0.size() ? z0[i] : 0);
        long long v2 = (i < z2.size() ? z2[i] : 0);
        z1[i] -= v0 + v2;
    }

    vector<long long> res(2 * n, 0);
    for (size_t i = 0; i < z0.size(); i++) res[i] += z0[i];
    for (size_t i = 0; i < z1.size(); i++) res[i + k] += z1[i];
    for (size_t i = 0; i < z2.size(); i++) res[i + 2 * k] += z2[i];
    while (res.size() > 1 && res.back() == 0) res.pop_back();
    return res;
}

string termLabel(int power) {
    if (power == 0) return "hang so (x^0)";
    if (power == 1) return "x";
    return "x^" + to_string(power);
}

void printPrettyPoly(const vector<long long>& p, const string& name) {
    cout << name << " = ";
    bool first = true;
    // in tu bac cao xuong bac thap
    for (int i = (int)p.size() - 1; i >= 0; i--) {
        long long c = p[i];
        if (c == 0 && p.size() > 1) continue;

        if (!first) {
            if (c >= 0) cout << " + ";
            else {
                cout << " - ";
                c = -c;
            }
        } else if (c < 0) {
            cout << "-";
            c = -c;
        }

        if (i == 0) {
            cout << c;
        } else if (i == 1) {
            if (c != 1) cout << c;
            cout << "x";
        } else {
            if (c != 1) cout << c;
            cout << "x^" << i;
        }
        first = false;
    }
    if (first) cout << 0;
    cout << endl;

}

int main() {
    cout << "===== NHAN HAI DA THUC (TIN HIEU) BANG FFT =====" << endl;

    int n, m;
    cout << "\nNhap so he so cua da thuc A: " << flush;
    cin >> n;
    if (n <= 0) {
        cout << "So he so khong hop le." << endl;
        cout << "\nNhan Enter de thoat...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return 0;
    }

    vector<long long> A(n);
    for (int i = n - 1; i >= 0; i--) {
        cout << "  He so cua " << termLabel(i) << ": " << flush;
        cin >> A[i];
    }

    cout << "\nNhap so he so cua da thuc B: " << flush;
    cin >> m;
    if (m <= 0) {
        cout << "So he so khong hop le." << endl;
        cout << "\nNhan Enter de thoat...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return 0;
    }

    vector<long long> B(m);
    for (int i = m - 1; i >= 0; i--) {
        cout << "  He so cua " << termLabel(i) << ": " << flush;
        cin >> B[i];
    }

    cout << "\n--- Da thuc vua nhap ---\n";
    printPrettyPoly(A, "A(x)");
    printPrettyPoly(B, "B(x)");

    auto C = multiplyFFT(A, B);
    cout << "\n--- Ket qua A(x) * B(x) ---\n";
    printPrettyPoly(C, "C(x)");

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    return 0;
}
