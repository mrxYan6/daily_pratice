#include <vector>
#include <iostream>
#include <queue>
using i64 = long long;

constexpr i64 inf = 1e18;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<int,int>>> adj(n);
    for (int i = 0; i < m; ++i) {
        int a, b, d;
        std::cin >> a >> b >> d;
        --a, --b;
        adj[a].emplace_back(b, -d);
        adj[b].emplace_back(a, d);
    }

    std::vector<i64> dis(n, inf);

    for (int i = 0; i < n; ++i) {
        if (dis[i] == inf) {
            dis[i] = 0;
            std::queue<int> q;
            q.emplace(i);

            while (!q.empty()) {
                int x = q.front();
                q.pop();

                for (auto [y, d] : adj[x]) {
                    if (dis[y] == inf) {
                        dis[y] = dis[x] + d;
                        q.push(y);
                    } else if (dis[y] != dis[x] + d) {
                        std::cout << "No\n";
                        return; 
                    }
                }
            }
        }
    }

    std::cout << "Yes\n";
}


int main(){ 
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}