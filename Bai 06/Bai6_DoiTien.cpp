#include <iostream>
using namespace std;

int main() {
    int N;
    int menhGia[] = {500000, 200000, 100000, 50000, 20000, 10000, 5000, 2000, 1000};
    int soMenhGia = sizeof(menhGia) / sizeof(menhGia[0]);

    cout << "===== BAI 6: DOI TIEN TAI NGAN HANG =====\n";
    cout << "Nhap so tien N: ";
    cin >> N;

    if (N <= 0) {
        cout << "So tien phai lon hon 0!\n";
        return 0;
    }

    int conLai = N;
    int tongTo = 0;

    cout << "\nKet qua doi tien:\n";

    for (int i = 0; i < soMenhGia; i++) {
        int soTo = conLai / menhGia[i];

        if (soTo > 0) {
            cout << menhGia[i] << " VND: " << soTo << " to\n";
            tongTo += soTo;
            conLai %= menhGia[i];
        }
    }

    cout << "\nTong so to tien it nhat: " << tongTo << " to\n";

    if (conLai != 0) {
        cout << "Con lai khong doi duoc: " << conLai << " VND\n";
    } else {
        cout << "Doi tien thanh cong!\n";
    }

    return 0;
}
