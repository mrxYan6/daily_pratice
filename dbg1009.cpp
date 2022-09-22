#include <iostream>
#include <queue>
#include <set>

using namespace std;

struct nod {
    int cost, x, y;

    nod(int cost, int x, int y) : cost(cost), x(x), y(y) {}

    bool operator<(const nod &rhs) const {
        return cost > rhs.cost;
    }
};

char mp[110][110];
int col[2500][2500];
int ans[110][110];
const int INF = 0x3f3f3f3f;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int n, m;

bool inmp(int x, int y) {
    return x > 0 && x <= n && y > 0 && y <= m;
}


int main() {
    int t;
    cin >> t;
    while (t--) {
        memset(mp, 0, sizeof(mp));
        memset(ans, 0x3f, sizeof(ans));
        cin >> n >> m;
        int x0, y0, x1, y1;
        cin >> x0 >> y0 >> x1 >> y1;
        for (int i = 1; i <= n; ++i)cin >> (mp[i] + 1);
        priority_queue<nod> q;
        ans[x0][y0] = 0;
        q.emplace(0, x0, y0);
        while (!q.empty()) {
            auto now = q.top();
            q.pop();
            if (now.x == x1, now.y == y1)break;
            for (int dir = 0; dir < 4; ++dir) {
                int nx = now.x + dx[dir], ny = now.y + dy[dir];
                if (inmp(nx, ny) && mp[nx][ny] == '.')
                    if (ans[nx][ny] > now.cost) {
                        ans[nx][ny] = now.cost;
                        q.emplace(now.cost, nx, ny);
                    }
            }
            for (int i = -2; i <= 2; ++i) {
                for (int j = -2; j <= 2; ++j) {
                    if (i == 0 && j >= -1 && j <= -1)continue;
                    if (j == 0 && i >= -1 && j <= -1)continue;
                    int nx = now.x + i, ny = now.y + j;
                    if (inmp(nx, ny) && mp[nx][ny] == '.') {
                        if (ans[nx][ny] > now.cost + 1) {
                            ans[nx][ny] = now.cost + 1;
                            q.emplace(now.cost + 1, nx, ny);
                        }
                    }
                }
            }
        }
        cout << ans[x1][y1] << endl;
    }
    return 0;
}