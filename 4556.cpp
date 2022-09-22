//
// Created by meiru on 2022/1/29.
//

#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;
const int N = 1e5 + 5;
int top[N], son[N], si[N], f[N], d[N];
int tim, NID[N], OID[N];
struct edg {
    int v, nxt;
};
vector<edg> E;
int head[N];
#define lson l,m,n<<1
#define rson m+1,r,n<<1|1
int arr[N];
struct t {
    int MAX;
    int id;
} tre[N << 2];
struct opt {
    int l, r, k;
};
vector<opt> o;
vector<int> a[N];

void dfs1(int x, int fa) {
    f[x] = fa, son[x] = 0, d[x] = d[fa] + 1, si[x] = 1;
    for (int i = head[x]; i != -1; i = E[i].nxt) {
        int v = E[i].v;
        if (v == fa)continue;
        dfs1(v, x);
        si[x] += si[v];
        if (si[son[x]] < si[v])son[x] = v;
    }
}

void dfs2(int x, int topx) {
    top[x] = topx;
    NID[x] = ++tim;
    OID[tim] = x;
    if (son[x])dfs2(son[x], topx);
    for (int i = head[x]; i != -1; i = E[i].nxt) {
        int v = E[i].v;
        if (v != f[x] && v != son[x])dfs2(v, v);
    }
}

void pushup(int n) {
    if (tre[n << 1].MAX >= tre[n << 1 | 1].MAX)tre[n].id = tre[n << 1].id;
    else tre[n].id = tre[n << 1 | 1].id;
    tre[n].MAX = max(tre[n << 1].MAX, tre[n << 1 | 1].MAX);
}

void build(int l, int r, int n) {
    if (l == r) {
        tre[n].MAX = 0;
        tre[n].id = l;
        return;
    }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    pushup(n);
}

void upd(int pos, int val, int l, int r, int n) {
    if (l == r) {
        tre[n].MAX += val;
        return;
    }
    int m = (l + r) >> 1;
    if (pos <= m)upd(pos, val, lson);
    else upd(pos, val, rson);
    pushup(n);
}

void chain(int x, int y, int k) {
    while (top[x] != top[y]) {
        if (d[top[x]] < d[top[y]])swap(x, y);
        o.push_back({NID[top[x]], NID[x], k});
        x = f[top[x]];
    }
    if (d[x] > d[y])swap(x, y);
    o.push_back({NID[x], NID[y], k});
}

int main() {
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif
    int n, m;
    cin >> n >> m ;
        memset(head, -1, sizeof head);
        tim = 0;
        E.clear();
        o.clear();
        memset(a, 0, sizeof a);
        for (int i = 1; i <= n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            E.push_back({v, head[u]});
            head[u] = E.size() - 1;
            E.push_back({u, head[v]});
            head[v] = E.size() - 1;
        }
        dfs1(1, 0);
        dfs2(1, 1);
        while (m--) {
            int x, y, k;
            cin >> x >> y >> k;
            chain(x, y, k);
        }
        for (auto x: o) {
            int l = x.l, r = x.r, k = x.k;
            a[l].push_back(k);
            a[r + 1].push_back(-k);
        }
        for (int i = 1; i <= n; ++i)sort(a[i].begin(), a[i].end());
        build(1, N, 1);
        vector<int> ans(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < a[i].size(); j++) {
                int tmp = a[i][j];
                if (tmp < 0)
                    upd(-tmp, -1, 1, N, 1);
                else
                    upd(tmp, 1, 1, N, 1);
            }
            ans[OID[i]] = tre[1].id;
            if (tre[1].MAX == 0)
                ans[OID[i]] = 0;
        }
        for (int i = 1; i <= n; ++i)cout << ans[i] << endl;
    
    return 0;
}