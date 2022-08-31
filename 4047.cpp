//
// Created by mrx on 2022/5/20.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

struct point {
    int x, y;

    point(int _x, int _y) : x(_x), y(_y) {}

    friend double dis(point &a, point &b) {
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }
};

struct edge {
    int u, v;
    double w;

    edge(int _u, int _v, double _w) : u(_u), v(_v), w(_w) {}

    bool operator<(const edge &rhs) const {
        return w < rhs.w;
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
    int n, k;
    cin >> n >> k;
    vector<edge> edg;
    vector<int> DSU(n);
    vector<point> p;
    for (int i = 0; i < n; ++i) {
        int x, y;
        DSU[i] = i;
        cin >> x >> y;
        p.emplace_back(x, y);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            edg.emplace_back(i, j, dis(p[i], p[j]));
        }
    }
    std::sort(edg.begin(), edg.end());
    std::function<int(int)> find_DSU = [&](int x) -> int {
        return x == DSU[x] ? x : DSU[x] = find_DSU(DSU[x]);
    };
    std::function<void(int, int)> merge_DSU = [&](int x, int y) {
        if (find_DSU(x) != find_DSU(y))DSU[find_DSU(x)] = find_DSU(y);
    };
    double ans, cnt = 0;
    for (auto x: edg) {
        int u = x.u, v = x.v;
        if (find_DSU(u) != find_DSU(v)) {
            ans = x.w;
            if (cnt == n - k)break;
            merge_DSU(u, v);
            cnt++;
        }
    }
    cout << fixed << setprecision(2) << ans << endl;
    return 0;
}