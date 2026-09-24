#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int findMaxMerge(const vector<int>& arr, int l, int r) {
    if (l == r) return arr[l]; 
    int mid = (l + r) / 2;
    int leftMax = findMaxMerge(arr, l, mid);
    int rightMax = findMaxMerge(arr, mid + 1, r);
    return max(leftMax, rightMax);
}

int main() {
    vector<int> temps = {30, 32, 29, 35, 33, 36, 31, 34, 37, 38, 29, 28};

    int globalMax = findMaxMerge(temps, 0, temps.size() - 1);

    cout << "Nhiet do cao nhat trong ngay: " << globalMax << " do C" << endl;

    return 0;
}