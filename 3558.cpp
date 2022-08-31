//
// Created by mrx on 2022/5/30.
//


#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;
const int INF = 0x3f3f3f3f;

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif
    int n;
    std::cin >> n;
    std::vector<std::array<int, 3>> dp(n);
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i)std::cin >> a[i];
    for (int i = 0; i < n; ++i)std::fill(dp[i].begin(), dp[i].end(), INF);
    dp[0][a[0] + 1] = 0;
    for (int i = 1; i < n; ++i) {
        if (a[i] == -1) {
            dp[i][0] = std::min(dp[i][0], dp[i - 1][0]);
            dp[i][2] = std::min(dp[i][2], dp[i - 1][2] + 2);
        } else if (a[i] == 0) {
            dp[i][0] = std::min(dp[i][0], dp[i - 1][0] + 1);
            dp[i][1] = std::min({dp[i][1], dp[i - 1][1], dp[i - 1][0]});
            dp[i][2] = std::min(dp[i][2], dp[i - 1][2] + 1);
        } else {
            dp[i][0] = std::min(dp[i][0], dp[i - 1][0] + 2);
            dp[i][1] = std::min(dp[i][1], dp[i - 1][0] + 1);
            dp[i][2] = std::min({dp[i][2], dp[i - 1][2], dp[i - 1][1], dp[i - 1][0]});
        }
    }
    if (dp[n - 1][0] == INF && dp[n - 1][1] == INF && dp[n - 1][2] == INF)std::cout << "BRAK\n";
    else std::cout << std::min({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]}) << '\n';
    return 0;
}