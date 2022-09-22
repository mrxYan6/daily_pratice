//
// Created by mrx on 2022/7/10.
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
    vector<pair<int, int>> G[n + 1];
    for (int i = 1; i < n; ++i) {
        int u, v, p;
        cin >> u >> v >> p;
        G[u].emplace_back(v, p);
        G[v].emplace_back(u, p);
    }

    return 0;
}