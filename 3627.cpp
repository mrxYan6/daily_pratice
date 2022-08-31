//
// Created by mrx on 2022/5/28.
//

#include <bits/stdc++.h>

#define ll long long
#define endl '\n'

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#endif
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> G(n + 5);
    std::vector<int> f(n + 5, 0), val(n + 5, 0), wei(n + 5, 0);
    std::vector<int> low(n + 5, -1), dfn(n + 5, -1);
    std::vector<int> inStack(n + 5, 0);
    std::stack<int> s;
    int id = 0, scc = 0;
    std::function<void(int)> tarjan = [&](int u) -> void {
        low[u] = dfn[u] = ++id;
        inStack[u] = 1, s.push(u);
        for (auto v: G[u]) {
            if (dfn[v] == -1) {
                tarjan(v);
                low[u] = std::min(low[u], low[v]);
            } else if (inStack[v]) {
                low[u] = std::min(low[u], low[v]);
            }
        }
        if (low[u] == dfn[u]) {
            while (s.top() != u) {
                f[s.top()] = scc;
                val[scc] += wei[s.top()];
                inStack[s.top()] = 0;
                s.pop();
            }
            f[s.top()] = scc;
            val[scc] += wei[s.top()];
            inStack[s.top()] = 0;
            s.pop();
            scc++;
        }
    };

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
    }

    for (int i = 0; i < n; ++i) {
        std::cin >> wei[i];
    }

    int S, bar;
    std::cin >> S >> bar;
    S--;

    std::vector<int> isBar(n + 5, 0);

    for (int i = 0; i < bar; ++i) {
        int x;
        std::cin >> x;
        x--;
        isBar[x] = 1;
    }

    tarjan(S);

    std::vector<std::vector<int>> G_new(scc + 5);

    std::queue<int> q;
    std::vector<int> in(scc + 5, 0);
    for (int i = 0; i < n; ++i) {
        for (auto v: G[i]) {
            if (f[i])
                if (f[i] != f[v]) {
                    G_new[f[i]].push_back(f[v]);
                    in[f[v]]++;
                }
        }
    }

    q.push(f[S]);
    std::vector<int> dp(scc + 5, 0);
    dp[f[S]] = val[f[S]];

    while (!q.empty()) {
        auto now = q.front();
        q.pop();
        for (auto v: G_new[now]) {
            dp[v] = std::max(dp[v], dp[now] + val[v]);
            if (!(--in[v]))q.push(v);
        }
    }

    int ans = -1;
    for (int i = 0; i < n; ++i) {
        if (isBar[i]) {
            ans = std::max(ans, dp[f[i]]);
        }
    }

    std::cout << ans << endl;
    return 0;
}