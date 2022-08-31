//
// Created by mrx on 2022/7/9.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

template<class T>
T quickPow(T base, ll fact) {
    T ans = 1;
    while (fact) {
        if (fact & 1) ans = ans * base;
        base = base * base;
        fact >>= 1;
    }
    return ans;
}

void sol() {
    int n, r;
    cin >> n >> r;
    vector<double> prob(n + 1, 0);
    vector<vector<double>> dp(n + 1, vector<double>(r + 1, 0));
    vector<int> dmg(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> prob[i] >> dmg[i];
    }
    dp[1][1] = 1 - quickPow(1 - prob[1], r), dp[1][0] = quickPow(1 - prob[1], r);
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j <= min(i, r); ++j) {
            dp[i][j] += dp[i - 1][j] * quickPow(1 - prob[i], r - j);//如果i不选，那么有r-j轮都没选到他
            dp[i][j] += dp[i - 1][j - 1] * (1 - quickPow((1 - prob[i]), r - j + 1));
        }
    }
    double ans = dp[1][1] * dmg[1];
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j <= min(i - 1, r); ++j) {
            ans += dp[i - 1][j] * (1 - quickPow(1 - prob[i], r - j)) * dmg[i];
        }
    }
    cout << fixed << setprecision(10) << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif
    int t;
    cin >> t;
    while (t--)sol();
    return 0;
}