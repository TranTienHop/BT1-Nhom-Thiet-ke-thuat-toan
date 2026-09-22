#include <iostream>
using namespace std;

int timDoDaiLIS(int a[], int n) {
    int dp[1000];        
    int ketQua = 1;

    for (int i = 0; i < n; i++) {
        dp[i] = 1;       
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }
        if (dp[i] > ketQua) ketQua = dp[i];
    }
    return ketQua;
}

void inDayLIS(int a[], int n) {
    int dp[1000];
    int truoc[1000];    
    int viTriMax = 0;

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        truoc[i] = -1;
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                truoc[i] = j;
            }
        }
        if (dp[i] > dp[viTriMax]) viTriMax = i;
    }

    int dayLIS[1000];
    int k = 0;
    for (int i = viTriMax; i != -1; i = truoc[i]) {
        dayLIS[k] = a[i];
        k++;
    }

    cout << "Day LIS cu the: ";
    for (int i = k - 1; i >= 0; i--) {
        cout << dayLIS[i] << " ";
    }
    cout << endl;
}

int main() {
    int a[] = {10, 9, 2, 5, 3, 7, 101, 18};
    int n = 8;

    cout << "Day gia co phieu: ";
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\n\n";

    int doDai = timDoDaiLIS(a, n);
    cout << "Do dai day con tang dai nhat: " << doDai << endl;

    inDayLIS(a, n);

    return 0;
}
