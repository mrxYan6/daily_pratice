//
// Created by mrx on 2022/5/22.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

struct point {
    int x, y;

    friend double dist(point X, point Y) {
        return sqrt((X.x - Y.x) * (X.x - Y.x) + (X.y - Y.y) * (X.y - Y.y));
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
    int n;
    cin >> n;
    vector<point> p;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        p.push_back({x, y});
    }
    vector<vector<int>> G(n, vector<int>(n, 0));
    vector<vector<double>> dis(n, vector<double>(n, 1e9));
    vector<int> vis(n, -1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char c;
            cin >> c;
            if (c == '1') {
                G[i][j] = 1;
                dis[i][j] = dist(p[i], p[j]);
            }
            if (i == j)dis[i][j] = 0;
        }
    }

    //bfs
    auto bfs = [&](int x, int id) {
        queue<int> q;
        q.push(x);
        while (!q.empty()) {
            auto now = q.front();
            q.pop();
            if (vis[now] != -1)continue;
            vis[now] = id;
            for (int i = 0; i < n; ++i) {
                if (G[now][i]) {
                    if (vis[i] == -1) {
                        q.push(i);
                    }
                }
            }
        }
    };

    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (vis[i] == -1)bfs(i, cnt++);
    }

    vector<double> diam(cnt, 0);
    vector<double> maxdis(n, 0);

    //floyd
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        double MAXDIS = 0;
        for (int j = 0; j < n; ++j) {
            if (dis[i][j] < 1e9)MAXDIS = max(MAXDIS, dis[i][j]);
        }
        maxdis[i] = MAXDIS;
        diam[vis[i]] = max(diam[vis[i]], maxdis[i]);
    }

    double ans = 1e9;

    //cacal
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (vis[i] == vis[j])continue;
            ans = min(ans, max({diam[vis[i]], diam[vis[j]], dist(p[i], p[j]) + maxdis[i] + maxdis[j]}));
        }
    }

    cout << fixed << setprecision(6) << ans << endl;
    return 0;
}

