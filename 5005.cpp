//
// Created by mrx on 2022/6/28.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;
const long long mod = 1e9 + 7;
long long m;

bool check1(long long j, long long k) {
    return (((j & (~(j >> 1))) & (k >> 2)) || ((j & (~(j << 1))) & (k << 2)) || (((k & (~(k >> 1))) & (j >> 2))) || ((k & (~(k << 1))) & (j << 2)));
}

bool check2(long long j, long long k, long long l) {
    return (((j & (~k)) & (l >> 1)) || ((j & (~k)) & (l << 1)) || ((l & (~k)) & (j >> 1)) || ((l & (~k)) & (j << 1)));
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
    long long n;
    cin >> n >> m;
    vector<vector<vector<ll>>> dp(2, vector<vector<ll>>(1 << m, vector<ll>(1 << m, 0)));
    for (long long i = 0; i < 1 << m; ++i) {
        dp[1][i][0] = 1;
    }
    for (long long i = 0; i < 1 << m; ++i) {
        for (long long j = 0; j < 1 << m; ++j) {
            if (check1(i, j))continue;
            else dp[0][j][i] = (dp[0][j][i] + dp[1][i][0]) % mod;
        }
    }
    for (long long i = 3; i <= n; ++i) {
        long long cur = i % 2;
        long long pre = (i - 1) % 2;
        for (long long s3 = 0; s3 < (1 << m); ++s3) {
            for (long long s2 = 0; s2 < (1 << m); ++s2) {
                dp[cur][s3][s2] = 0;
                if (check1(s3, s2))continue;
                for (long long s1 = 0; s1 < (1 << m); ++s1) {
                    if (check2(s1, s2, s3))continue;
                    dp[cur][s3][s2] = (dp[cur][s3][s2] + dp[pre][s2][s1]) % mod;
                }
            }
        }
    }
    long long ans = 0;
    long long cur = n % 2;
    for (long long s1 = 0; s1 < (1 << m); ++s1) {
        for (long long s2 = 0; s2 < (1 << m); ++s2) {
            if (check1(s1, s2))continue;
            ans = (ans + dp[cur][s1][s2]) % mod;
        }
    }
    cout << ans << endl;
    return 0;
}
