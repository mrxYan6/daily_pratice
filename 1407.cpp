//
// Created by mrx on 2022/4/26.
//

#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;
const int N = 4020;
vector<int> G[2 * N];
vector<int> dfn(N * 2, -1), low(2 * N, -1), f(2 * N, -1);
stack<int> s;
bool inStack[2 * N] = {false};
int scc, cnt;

void tarjan(int u) {
    s.push(u);
    inStack[u] = true;
    dfn[u] = low[u] = ++cnt;
    for (auto x: G[u]) {
        if (dfn[x] == -1) {
            tarjan(x);
            low[u] = min(low[u], low[x]);
        } else if (inStack[x]) {
            low[u] = min(low[u], low[x]);
        }
    }
    if (dfn[u] == low[u]) {
        while (u != s.top()) {
            f[s.top()] = scc;
            inStack[s.top()] = false;
            s.pop();
        }
        f[s.top()] = scc;
        inStack[s.top()] = false;
        s.pop();
        scc++;
    }
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
    int n, m;
    cin >> n;

    map<string, int> name;
    for (int i = 0; i < n; ++i) {
        string fe, ma;
        cin >> fe >> ma;
        name[fe] = i;
        name[ma] = i + n;
        G[i].push_back(i + n);
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        string fe, ma;
        cin >> fe >> ma;
        int fid = name[fe], mid = name[ma];
        G[mid].push_back(fid);
    }
    scc = 0, cnt = 0;
    for (int i = 0; i < n; ++i)if (dfn[i] == -1)tarjan(i);
    for (int i = 0; i < n; ++i) {
        if (f[i] == f[i + n])cout << "Unsafe\n";
        else cout << "Safe\n";
    }
    return 0;
}