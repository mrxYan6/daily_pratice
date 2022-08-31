//
// Created by mrx on 2022/5/22.
//


#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

struct square {
    int len, hei;

    square(int l, int h) : len(l), hei(h) {}
};

const int N = 1e3 + 100;
int h[N][N], l[N][N], r[N][N], mp[N][N];

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif
    int n, m;
    cin >> n >> m;
    memset(h, 0, sizeof h);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            char x;
            cin >> x;
            if (x == 'F') {
                mp[i][j] = 1;
                h[i][j] = h[i - 1][j] + 1;
                l[i][j] = r[i][j] = j;
            } else h[i][j] = 0;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 2; j <= m; ++j) {
            if (mp[i][j] && mp[i][j - 1])
                l[i][j] = l[i][j - 1];
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = m - 1; j; --j) {
            if (mp[i][j] && mp[i][j + 1])
                r[i][j] = r[i][j + 1];
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (mp[i][j] && mp[i - 1][j]) {
                l[i][j] = max(l[i][j], l[i - 1][j]);
                r[i][j] = min(r[i][j], r[i - 1][j]);
            }
            ans = max(ans, h[i][j] * (r[i][j] - l[i][j] + 1));
        }
    cout << ans * 3 << endl;
    return 0;
}