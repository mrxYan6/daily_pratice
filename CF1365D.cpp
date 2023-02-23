//
// Created by mrx on 2023/2/22.
//
#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <queue>
#include <array>
#include <map>

using i64 = long long;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector mp(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            std::cin >> c;
            if (c == 'G') mp[i][j] = 1;
            else if (c == '#') mp[i][j] = -1;
            else if (c == 'B')mp[i][j] = 2;
            else mp[i][j] = 0;
        }
    }

    auto in = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m;
    };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mp[i][j] == 2) {
                for (int d = 0; d < 4; ++d) {
                    int nx = i + dx[d], ny = j + dy[d];
                    if (in(nx, ny)) {
                        if (mp[nx][ny] == 1) {
                            std::cout << "no\n";
                            return;
                        } else if (mp[nx][ny] == 0)mp[nx][ny] = -1;
                    }
                }
            }
        }
    }

    std::queue<std::pair<int, int>> q;
    std::vector vis(n, std::vector<bool>(m));
    if (mp[n - 1][m - 1] == 0)q.emplace(n - 1, m - 1);
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        if (vis[x][y])continue;
        vis[x][y] = true;
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (in(nx, ny) && mp[nx][ny] != -1 && !vis[nx][ny]) {
                q.emplace(nx, ny);
            }
        }
    }

    bool ok = true;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mp[i][j] == 1 && !vis[i][j])ok = false;
            if (mp[i][j] == 2 && vis[i][j])ok = false;
        }
    }
    if (ok)std::cout << "yes\n";
    else std::cout << "no\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}