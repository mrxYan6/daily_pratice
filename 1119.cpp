//
// Created by mrx on 2022/5/21.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

struct nod {
    int pos;
    ll val;

    nod(int p, ll v) : pos(p), val(v) {}

    bool operator<(const nod &rhs) const {
        return val > rhs.val;
    }
};

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
    vector<int> t(n);
    vector<vector<ll>> dis(n, vector<ll>(n, 0x3f3f3f3f3f3f3f3f));
    vector<pair<int, int>> p;
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
        p.emplace_back(t[i], i);
    }
    std::sort(p.begin(), p.end());
    int ptr = 0;
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        dis[u][v] = w;
        dis[v][u] = w;
    }
    int q;
    cin >> q;
    while (q--) {
        int x, y, T;
        cin >> x >> y >> T;
        while (p[ptr].first <= T) {
            int k = p[ptr].second;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dis[i][j] > dis[i][k] + dis[k][j])
                        dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
            ptr++;
        }
        if (t[x] > T || t[y] > T)cout << -1 << endl;
        else if (dis[x][y] == 0x3f3f3f3f3f3f3f3f)cout << -1 << endl;
        else cout << dis[x][y] << endl;
    }
    return 0;
}