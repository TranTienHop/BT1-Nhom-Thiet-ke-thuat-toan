#include <iostream>
#include <vector>

using namespace std;

int binarySearch(const vector<int>& a, int target) {
    int left = 0;
    int right = a.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (a[mid] == target) {
            return mid;
        } else if (a[mid] < target) {
            left = mid + 1; 
        } else {
            right = mid - 1; 
        }
    }

    return -1;
}

int main() {
    int n;
    cout << "Nhap so luong san pham trong kho: ";
    cin >> n;

    vector<int> productIDs(n);
    cout << "Nhap cac ma san pham (da duoc sap xep tang dan):\n";
    for (int i = 0; i < n; i++) {
        cin >> productIDs[i];
    }

    int target;
    cout << "Nhap ma san pham can tim: ";
    cin >> target;

    int resultIndex = binarySearch(productIDs, target);

    if (resultIndex != -1) {
        cout << "Ket qua: San pham co ton tai trong kho (tai vi tri chi so " << resultIndex << ").\n";
    } else {
        cout << "Ket qua: San pham khong ton tai trong kho.\n";
    }

    return 0;
}
