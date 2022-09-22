//
// Created by mrx on 2022/5/24.
//

#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;
const int N = 550;
int pre[N];
vector<int> EDG[N];
stack<int> vis;
bool use[N];

int dfs(int x) {
    for (int i = 0; i < EDG[x].size(); ++i) {
        if (!use[EDG[x][i]]) {
            use[EDG[x][i]] = true;
            vis.push(EDG[x][i]);
            if (pre[EDG[x][i]] == 0 || dfs(pre[EDG[x][i]])) {
                pre[EDG[x][i]] = x;
                return 1;
            }
        }
    }
    return 0;
}

int hungary(int n) {
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (dfs(i))sum++;
        while (!vis.empty()) {
            use[vis.top()] = false;
            vis.pop();
        }
    }
    return sum;
}

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
    int n, m, e;
    cin >> n >> m >> e;
    memset(use, 0, sizeof use);
    memset(pre, 0, sizeof pre);
    for (int i = 1; i <= e; ++i) {
        int u, v;
        cin >> u >> v;
        EDG[u].push_back(v);
    }
    cout << hungary(n);
    return 0;
}