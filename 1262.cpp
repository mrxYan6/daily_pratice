//
// Created by mrx on 2022/5/26.
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
    int n;
    cin >> n;
    int p;
    cin >> p;
    vector<vector<int>> G(n, vector<int>());
    vector<int> dfn(n, -1), low(n, -1);
    vector<int> f(n), cost(n, 0x3f3f3f3f), wei(n, 0x3f3f3f3f);
    vector<bool> inStack(n, false);
    stack<int> s;
    int id = 0, scc = 0;
    std::function<void(int)> tarjan = [&](int u) -> void {
        dfn[u] = low[u] = ++id;
        s.push(u), inStack[u] = true;
        for (auto v: G[u]) {
            if (dfn[v] == -1) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (inStack[v]) {
                low[u] = min(low[u], low[v]);
            }
        }
        if (low[u] == dfn[u]) {
            while (s.top() != u) {
                int x = s.top();
                s.pop();
                f[x] = scc;
                cost[scc] = min(cost[scc], wei[x]);
                inStack[x] = false;
            }
            int x = s.top();
            s.pop();
            f[x] = scc;
            cost[scc] = min(cost[scc], wei[x]);
            inStack[x] = false;
            scc++;
        }
    };
    for (int i = 0; i < p; ++i) {
        int x, w;
        cin >> x >> w;
        x--;
        wei[x] = w;
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
    }
    for (int i = 0; i < n; ++i) {
        if (dfn[i] == -1)tarjan(i);
    }
    int ans = 0;
    vector<vector<int>> G_new(scc, vector<int>());
    vector<int> inDegree(scc, 0);
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        for (auto v: G[i]) {
            if (f[v] != f[i]) {
                G_new[f[i]].push_back(f[v]);
                inDegree[f[v]]++;
            }
        }
    }
    for (int i = 0; i < scc; ++i)
        if (inDegree[i] == 0) {
            if (cost[i] == 0x3f3f3f3f) {
                cout << "NO" << endl;
                for (int j = 0; j < n; ++j)if (f[j] == i)cout << j + 1 << endl;
                return 0;
            } else ans += cost[i];
        }
    cout << "YES\n" << ans << endl;
    return 0;
}