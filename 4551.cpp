//
// Created by mrx on 2022/5/4.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

struct Trie {
    Trie *nxt[2];

    Trie() {
        for (auto &x: nxt)x = nullptr;
    }
};

void insert(Trie *rt, int x) {
    Trie *p = rt;
    for (int i = 30; i >= 0; --i) {
        int id = 1 & (x >> i);
        if (p->nxt[id] == nullptr) {
            p->nxt[id] = new Trie;
        }
        p = p->nxt[id];
    }
}

const int N = 1e5 + 100;

vector<pair<int, int>> G[N];
int dis[N];

void dfs(int u, int rt) {
    for (auto [v, w]: G[u]) {
        if (v == rt)continue;
        dis[v] = dis[u] ^ w;
        dfs(v, u);
    }
}

int qry(Trie *root, int w) {
    Trie *p = root;
    int ans = 0;
    for (int i = 30; i >= 0; --i) {
        int id = 1 & (w >> i);
        if (p->nxt[!id] != nullptr) {
            ans += (1 << i);
            p = p->nxt[!id];
        } else {
            p = p->nxt[id];
        }
    }
    return ans;
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
    int n;
    cin >> n;
    Trie *trie = new Trie;
    for (int i = 1; i <= n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; ++i)insert(trie, dis[i]);
    int ans = 0;
    for (int i = 1; i <= n; ++i)ans = max(ans, qry(trie, dis[i]));
    cout << ans << endl;
    return 0;
}