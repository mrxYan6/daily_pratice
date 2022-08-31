#include <bits/stdc++.h>
#include <algorithm>
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
    int n, m;
    cin >> n >> m;
    vector <vector<int>> G(n, vector<int>());
    vector<int> dfn(n, -1), low(n, -1);
    vector<bool> flag(n, false);
    int id = 0;
    vector<int> cut;
    std::function<void(int, int)> tarjan = [&](int u, int fa) -> void {
        low[u] = dfn[u] = id++;
        int child = 0;
        for (auto v: G[u]) {
            if (v == fa)continue;
            if (dfn[v] == -1) {
                if (fa == u)child++;
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (!flag[u] && low[v] >= dfn[u] && fa != u) {
                    cut.push_back(u);
                    flag[u] = true;
                }
            } else {
                low[u] = min(low[u], dfn[v]);//!!!!!!!!!!
            }
        }
        if (child >= 2 && u == fa) {
            cut.push_back(u);
            flag[u] = true;
        }
        return;
    };
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 0; i < n; ++i)
        if (dfn[i] == -1)tarjan(i, i);
    cout << cut.size() << endl;
    std::sort(cut.begin(), cut.end());
    for (auto x: cut)cout << x + 1 << ' ';
    cout << endl;
    return 0;
}