#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

struct nod {
    int pos;
    ll val;

    nod(int pos, ll va) : pos(pos), val(va) {}

    bool operator<(const nod &rhs) const {
        return val > rhs.val;
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
    int n, m, b;
    cin >> n >> m >> b;
    vector<int> money(n);
    vector<ll> cost(n * 2, 0x3f3f3f3f3f3f3f3f);
    vector<pair<int, ll>> G[n * 2];
    auto dij = [&](int start, ll mid) {
        std::fill(cost.begin(), cost.end(), 0x3f3f3f3f3f3f3f3f);
        priority_queue<nod> q;
        if (money[start] > mid)return false;
        cost[start] = 0;
        q.emplace(start, 0);
        while (!q.empty()) {
            auto [u, dist] = q.top();
            q.pop();
            if (cost[u] != dist)continue;
            for (auto [v, w]: G[u]) {
                if (money[v] > mid)continue;
                if (cost[v] > cost[u] + w) {
                    cost[v] = cost[u] + w;
                    q.emplace(v, cost[v]);
                }
            }
        }
        return cost[n - 1] <= b;
    };
    for (int i = 0; i < n; ++i)cin >> money[i];
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--, v--;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    ll l = 0, r = 2e9, ans = -1;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        if (dij(0, mid)) {
            ans = mid;
            r = mid - 1;
        } else l = mid + 1;
    }
    if (ans == -1)cout << "AFK";
    else cout << ans;
    cout << endl;
    return 0;
}