//
// Created by mrx on 2022/5/24.
//

#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

struct NetworkFlow {
    struct edge {
        int u, v;
        ll cap, flow;

        edge(int _u, int _v, ll _cap, ll _flow) : u(_u), v(_v), cap(_cap), flow(_flow) {}
    };

    vector<edge> E;
    vector<vector<int>> G;
    int S, T;
    vector<int> dep, cur, vis;

    NetworkFlow(int n) {
        G.resize(n, vector<int>());
        dep.resize(n), cur.resize(n), vis.resize(n);
        E.clear();
    }

    void addEdge(int u, int v, int cap, int cap_) {
        G[u].push_back((int) E.size());
        E.emplace_back(u, v, cap, 0);
        G[v].push_back((int) E.size());
        E.emplace_back(v, u, cap_, 0);
    }

    bool bfs() {
        std::fill(vis.begin(), vis.end(), 0);
        queue<int> q;
        q.push(S);
        vis[S] = 1;
        dep[S] = 1;
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            for (auto edgeID: G[now]) {
                auto &e = E[edgeID];
                if (!vis[e.v] && e.cap > e.flow) {
                    vis[e.v] = 1;
                    dep[e.v] = dep[e.u] + 1;
                    q.push(e.v);
                }
            }
        }
        return vis[T];
    }

    ll dfs(int x, ll flow) {
        if (flow == 0 || x == T) {
            return flow;
        }
        ll now = 0, f;
        for (auto &w = cur[x]; w < G[x].size(); ++w) {
            edge &e = E[G[x][w]];
            if (dep[e.v] == dep[x] + 1 && (f = dfs(e.v, min(flow, e.cap - e.flow))) > 0) {
                e.flow += f;
                E[G[x][w] ^ 1].flow -= f;
                now += f;
                flow -= f;
                if (flow == 0)break;
            }
        }
        return now;
    }

    ll dinic(int s, int t) {
        S = s, T = t;
        ll flow = 0;
        while (bfs()) {
            std::fill(cur.begin(), cur.end(), 0);
            flow += dfs(S, 0x3f3f3f3f3f3f3f3f);
        }
        return flow;
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
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    //完蛋了网络瘤板子忘光了
    NetworkFlow solve(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        solve.addEdge(u - 1, v - 1, w, 0);
    }
    cout << solve.dinic(s - 1, t - 1) << endl;
    return 0;
}