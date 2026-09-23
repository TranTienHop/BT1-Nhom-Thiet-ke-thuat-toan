#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, W;

    cout << "Nhap so luong don hang: ";
    cin >> n;

    cout << "Nhap tai trong toi da cua xe: ";
    cin >> W;

    vector<int> weight(n + 1);
    vector<int> profit(n + 1);

    for (int i = 1; i <= n; i++) {
        cout << "Don hang " << i << ":\n";
        cout << "  Trong luong: ";
        cin >> weight[i];

        cout << "  Loi nhuan: ";
        cin >> profit[i];
    }

    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {

            dp[i][w] = dp[i - 1][w];

            if (weight[i] <= w) {
                dp[i][w] = max(
                    dp[i][w],
                    dp[i - 1][w - weight[i]] + profit[i]
                );
            }
        }
    }

    cout << "\nLoi nhuan toi da: " << dp[n][W] << endl;

    int w = W;
    vector<int> selected;

    for (int i = n; i >= 1; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            selected.push_back(i);
            w -= weight[i];
        }
    }

    reverse(selected.begin(), selected.end());

    cout << "Cac don hang duoc chon: ";
    for (int i : selected) {
        cout << i << " ";
    }

    cout << endl;

    return 0;
}
