//
// Created by mrx on 2022/6/28.
//


#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif
    int k, n;
    cin >> k >> n;
    vector<vector<double>> dp(k + 2, vector<double>(32799, 0));
    vector<int> val(n), key(n);
    for (int i = 0; i < n; ++i) {
        cin >> val[i];
        int x;
        int s = 0;
        while (cin >> x && x) {
            s |= 1 << (x - 1);
        }
        key[i] = s;
    }
    for (int i = k - 1; i >= 0; --i) {
        for (int sta = 0; sta < (1 << n); ++sta) {
            for (int j = 0; j < n; ++j) {
                if ((sta & key[j]) == key[j]) {
                    dp[i][sta] += max(dp[i + 1][sta], dp[i + 1][sta | (1 << j)] + val[j]);
                } else dp[i][sta] += dp[i + 1][sta];
            }
            dp[i][sta] /= n;
        }
    }
    cout << fixed << setprecision(6) << dp[0][0] << endl;
    return 0;
}