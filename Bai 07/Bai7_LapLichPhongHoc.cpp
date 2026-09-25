#include <iostream>
#include <algorithm>
using namespace std;

struct LopHoc {
    int batDau;
    int ketThuc;
};

bool sapXep(LopHoc a, LopHoc b) {
    return a.batDau < b.batDau;
}

int main() {
    int n;

    cout << "Nhap so luong lop hoc: ";
    cin >> n;

    LopHoc lop[100];
    
    for (int i = 0; i < n; i++) {
        cout << "Lop " << i + 1 << ":\n";
        cout << "  Thoi gian bat dau: ";
        cin >> lop[i].batDau;
        cout << "  Thoi gian ket thuc: ";
        cin >> lop[i].ketThuc;
    }

    sort(lop, lop + n, sapXep);

    int phong[100];
    int soPhong = 0;

    for (int i = 0; i < n; i++) {
        bool daXep = false;

        for (int j = 0; j < soPhong; j++) {
            if (phong[j] <= lop[i].batDau) {
                phong[j] = lop[i].ketThuc;
                daXep = true;
                break;
            }
        }

        if (!daXep) {
            phong[soPhong] = lop[i].ketThuc;
            soPhong++;
        }
    }

    cout << "\nSo phong hoc can dung: " << soPhong << endl;

    return 0;
}
