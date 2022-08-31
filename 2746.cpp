//
// Created by mrx on 2022/5/24.
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
    vector<vector<int>> G(n, vector<int>());
    vector<bool> inStack(n, false);
    vector<int> dfn(n, -1), low(n, -1);
    vector<int> f(n);
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
            }
            s.pop();
            inStack[u] = false;
            f[u] = sccCnt;
            sccCnt++;
        }
        return;
    };
    for (int i = 0; i < n; ++i) {
        int x;
        while (cin >> x && x) {
            G[i].push_back(x - 1);
        }
    }
    for (int i = 0; i < n; ++i)if (dfn[i] == -1)tarjan(i);
    vector<int> inDegree(sccCnt, 0), outDegree(sccCnt, 0);
    for (int i = 0; i < n; ++i) {
        for (auto v: G[i]) {
            if (f[i] != f[v]) {
                outDegree[f[i]]++;
                inDegree[f[v]]++;
            }
        }
    }
    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < sccCnt; ++i) {
        if (inDegree[i] == 0)cnt1++;
        if (outDegree[i] == 0)cnt2++;
    }
    cout << cnt1 << endl << (sccCnt == 1 ? 0 : max(cnt1, cnt2)) << endl;
    return 0;
}