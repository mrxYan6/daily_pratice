//
// Created by mrx on 2022/5/22.
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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> G(n, vector<int>());
    vector<bool> inStack(n, false);
    vector<int> dfn(n, -1), low(n, -1);
    vector<int> f(n), val(n);
    stack<int> s;
    int id = 0, sccCnt = 0;
    std::function<void(int)> tarjan = [&](int u) -> void {
        low[u] = dfn[u] = id++;
        s.push(u), inStack[u] = true;
        for (auto v: G[u]) {
            if (dfn[v] == -1) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (inStack[v]) {
                low[u] = min(low[u], low[v]);
            }
        }
        if (dfn[u] == low[u]) {
            while (s.top() != u) {
                auto x = s.top();
                s.pop();
                inStack[x] = false;
                f[x] = sccCnt;
                val[sccCnt]++;
            }
            s.pop();
            inStack[u] = false;
            f[u] = sccCnt;
            val[sccCnt]++;
            sccCnt++;
        }
        return;
    };
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
    }
    for (int i = 0; i < n; ++i)if (dfn[i] == -1)tarjan(i);
    vector<vector<int>> G_new(sccCnt, vector<int>());
    vector<int> outD(sccCnt, 0);
    for (int i = 0; i < n; ++i) {
        for (auto x: G[i]) {
            if (f[x] != f[i]) {
                outD[f[i]]++;
            }
        }
    }
    vector<int> ans;
    for (int i = 0; i < sccCnt; ++i) {
        if (outD[i] == 0)ans.push_back(i);
    }
    if (ans.size() > 1)cout << 0 << endl;
    else cout << val[ans[0]] << endl;
    return 0;
}