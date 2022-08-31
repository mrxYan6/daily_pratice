//
// Created by mrx on 2022/7/11.
//

#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y);
    ll t = x;
    x = y;
    y = t - a / b * x;
    return d;
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
    double p;
    int n, k;
    cin >> p >> n >> k;
    vector<vector<double>> dp(2, vector<double>(n + 1, 0));
    vector<double> p2(n + 1, 0), sum(n + 1, 0);
    sum[0] = 1, p2[0] = 1;
    for (int i = 1; i <= n; ++i) {
        p2[i] = p2[i - 1] * (1 - p);
        sum[i] = sum[i - 1] + p2[i];
    }
    if (p == 0) {
        cout << 0 << endl;
        return 0;
    }
    dp[1][1] = 1;
    for (int i = 2; i <= n; ++i) {
        double a = sum[i - 1];
        double b = 0;
        for (int j = 0; j <= i - 2; ++j) {
            b += p * dp[(i - 1) % 2][i - 1 - j] * sum[j];
        }
        dp[i % 2][1] = (1 - b) / a;
        for (int j = 2; j <= i; ++j) {
            dp[i % 2][j] = dp[(i - 1) % 2][j - 1] * p + dp[i % 2][j - 1] * (1 - p);
        }
    }
    cout << fixed << setprecision(9) << dp[n % 2][k] << endl;
    return 0;
}