//
// Created by mrx on 2022/6/28.
//

#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

void sol() {
    int n;
    cin >> n;
    vector<int> cnt(n + 1, 0), taste(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> taste[i] >> cnt[i];
    }
    vector<vector<vector<int>>> dp(n + 2, vector<vector<int>>(20, vector<int>(1 << 8, 0x3f3f3f3f)));
    //i表示第一个没打饭的，j表示当前最后一个打饭的，k表示i后面的8个人打饭的状态
    dp[1][9][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int s = 0; s < (1 << 8); ++s) {
            for (int j = -8; j <= 7; ++j) {
                if (dp[i][j + 10][s] == 0x3f3f3f3f)continue;
                if (s & 1) {
                    dp[i + 1][j + 9][s >> 1] = min(dp[i + 1][j + 9][s >> 1], dp[i][j + 10][s]);
                } else {
                    int rig = 8;
                    for (int nxt = 0; nxt <= rig; ++nxt) {
                        if (!((s >> nxt) & 1)) {
                            rig = min(rig, nxt + cnt[nxt + i]);
                            if (nxt > rig)break;
                            dp[i][nxt + 10][s | (1 << (nxt))] = min(dp[i][nxt + 10][s | (1 << (nxt))],
                                                                    dp[i][j + 10][s] + (i + j == 0 ? 0 : (taste[i + j] ^ taste[nxt + i])));
                        }
                    }
                }
            }
        }
    }
    int ans = 0x3f3f3f3f;
    for (int i = 0; i <= 8; ++i) {
        ans = min(ans, dp[n + 1][10 - i][0]);
    }
    cout << ans << endl;
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
    while (t--) sol();
    return 0;
}