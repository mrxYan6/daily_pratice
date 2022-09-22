//
// Created by mrx on 2022/5/14.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <queue>

#define ll long long
#define endl '\n'
using namespace std;
const int N = 1030;
int mp[N][N];
bool vis[N][N];
int n, m;

struct nod {
    int x, y, val, col;

    nod(int x, int y, int v, int c) : x(x), y(y), val(v), col(c) {}

    bool operator<(const nod &rhs) const {
        return val > rhs.val;
    }
};

bool in(int x, int y) {
    return x > 0 && x <= m && y > 0 && y <= m;
}

int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

void bfs() {
    priority_queue<nod> q;
    q.emplace(1, 1, 0, mp[1][1]);
    while (!q.empty()) {
        auto now = q.top();
        q.pop();
        if (vis[now.x][now.y])continue;
        vis[now.x][now.y] = true;
        if (now.x == m && now.y == m) {
            cout << now.val << endl;
            return;
        }

        for (int dir = 0; dir < 4; ++dir) {
            int nx = now.x + dx[dir], ny = now.y + dy[dir];
            if (in(nx, ny) && !vis[nx][ny]) {
                if (mp[nx][ny] == -1) {
                    if (mp[now.x][now.y] == -1)continue;
                    else {
                        q.emplace(nx, ny, now.val + 2, now.col);
                    }
                } else {
                    q.emplace(nx, ny, now.val + (now.col != mp[nx][ny]), mp[nx][ny]);
                }
            }
        }
    }
    cout << -1 << endl;
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
    cin >> m >> n;
    memset(mp, -1, sizeof mp);
    memset(vis, 0, sizeof vis);
    for (int i = 0; i < n; ++i) {
        int x, y, c;
        cin >> x >> y >> c;
        mp[x][y] = c;
    }
    bfs();

    return 0;
}