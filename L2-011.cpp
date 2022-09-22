#include <bits/stdc++.h>

using namespace std;

const int N = 33;

int xx[N], zx[N];
vector<int> layor[N];
struct t {
    int val;
    int ls, rs;
} t[N << 2];
int cnt = 0;

int dfs(int l, int r, int rt) {
    int root = ++cnt;
    t[root].ls = t[root].rs = -1;
    t[root].val = zx[rt];
    if (l == r)return root;
    int sonrt = 0, sonrtid = 0;
    for (int i = l; i <= r; ++i) {
        if (zx[rt] == xx[i]) {
            sonrt = xx[i];
            sonrtid = i;
            break;
        }
    }
    if (l < sonrtid)t[root].ls = dfs(l, sonrtid - 1, rt + 1);
    if (sonrtid < r)t[root].rs = dfs(sonrtid + 1, r, rt + 1 + sonrtid - l);
    return root;
}

void dfs2(int id, int dpt) {
    layor[dpt].push_back(t[id].val);
    if (t[id].rs != -1)dfs2(t[id].rs, dpt + 1);
    if (t[id].ls != -1)dfs2(t[id].ls, dpt + 1);
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)cin >> xx[i];//zgy
    for (int i = 1; i <= n; ++i)cin >> zx[i];//gzy
    dfs(1, n, 1);
    dfs2(1, 1);
    vector<int> ans;
    for (int i = 1; i <= n; ++i) {
        for (auto x: layor[i])
            ans.push_back(x);
    }
    cout << ans[0];
    for (int i = 1; i < ans.size(); ++i)cout << ' ' << ans[i];
    cout << endl;
}