//
// Created by mrx on 2022/4/10.
//

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 1000;
std::vector<int> g[N];

int dep[N], col[N], si[N], fa[N], son[N], top[N], pos[N], oid[N];
int t, LCol, RCol;

void dfs1(int u, int f) {
    dep[u] = dep[f] + 1, son[u] = 0;
    fa[u] = f, si[u] = 1;
    for (auto v: g[u]) {
        if (v != f) {
            dfs1(v, u);
            si[u] += si[v];
            if (si[son[u]] < si[v])son[u] = v;
        }
    }
}

void dfs2(int x, int topx) {
    top[x] = topx;
    pos[x] = ++t;
    oid[t] = x;
    if (son[x])dfs2(son[x], topx);
    for (auto v: g[x]) {
        if (v == fa[x] || v == son[x])continue;
        dfs2(v, v);
    }
}

#define L(x) x<<1
#define R(x) x<<1|1
#define T tre[rt]
#define LS tre[rt<<1]
#define RS tre[rt<<1|1]
struct seg {
    int num, lazy, lc, rc;
    int l, r;
} tre[N << 2];

void push_down(int rt) {
    if (T.lazy) {
        LS.lazy = RS.lazy = T.lazy;
        LS.num = RS.num = 1;
        LS.lc = LS.rc = T.lc;
        RS.lc = RS.rc = T.lc;
        T.lazy = 0;
    }
}

void push_up(int rt) {
    T.lc = LS.lc;
    T.rc = RS.rc;
    int ans = LS.num + RS.num;
    if (LS.rc == RS.lc)
        ans--;
    T.num = ans;
}

void build(int rt, int l, int r) {
    T.l = l;
    T.r = r;
    T.num = 0;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(L(rt), l, mid);
    build(R(rt), mid + 1, r);
}

void update(int rt, int l, int r, int x) {
    if (T.l == l && T.r == r) {
        T.num = T.lazy = 1;
        T.lc = T.rc = x;
        return;
    }
    push_down(rt);
    int mid = (T.l + T.r) >> 1;
    if (r <= mid)
        update(L(rt), l, r, x);
    else if (l > mid)
        update(R(rt), l, r, x);
    else {
        update(L(rt), l, mid, x);
        update(R(rt), mid + 1, r, x);
    }
    push_up(rt);
}

int query(int rt, int l, int r, int L, int R) {
    if (T.l == L)
        LCol = T.lc;
    if (T.r == R)
        RCol = T.rc;
    if (T.l == l && T.r == r)
        return T.num;
    push_down(rt);
    int mid = (T.l + T.r) >> 1;
    if (r <= mid)
        return query(L(rt), l, r, L, R);
    else if (l > mid)
        return query(R(rt), l, r, L, R);
    else {
        int ans = query(L(rt), l, mid, L, R) + query(R(rt), mid + 1, r, L, R);
        if (LS.rc == RS.lc)
            ans--;
        return ans;
    }
    push_up(rt);
}

int solve(int u, int v) {
    int ans = 0;
    int LefCol = -1, RigCol = -1;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])swap(u, v), swap(LefCol, RigCol);
        ans += query(1, pos[top[u]], pos[u], pos[top[u]], pos[u]);
        if (RCol == LefCol) ans--;
        LefCol = LCol;
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v), swap(LefCol, RigCol);
    ans += query(1, pos[v], pos[u], pos[v], pos[u]);
    if (RCol == LefCol) ans--;
    if (LCol == RigCol) ans--;
    return ans;
}

void upd(int u, int v, int c) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        update(1, pos[top[u]], pos[u], c);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    update(1, pos[u], pos[v], c);
}

//int a[N];
//
//inline void pushup(int rt) {
//    TRE.lc = LS.lc;
//    TRE.rc = RS.rc;
//    int ans = LS.num + RS.num;
//    if (LS.rc == RS.lc)ans--;
//    TRE.num = ans;
//}
//
//void build(int l, int r, int rt) {
//    TRE.l = l, TRE.r = r;
//    if (l == r) {
//        TRE.num = 1, TRE.lazy = 0;
//        TRE.lc = TRE.rc = a[oid[l]];
//        return;
//    }
//    int m = l + r >> 1;
//    build(lson);
//    build(rson);
//    pushup(rt);
//}
//
//inline void pushdown(int rt) {
//    if (TRE.lazy) {
//        RS.lazy = LS.lazy = TRE.lazy;
//        LS.num = RS.num = 1;
//        LS.lc = RS.lc = TRE.lc;
//        LS.rc = RS.rc = TRE.rc;
//        TRE.lazy = 0;
//    }
//}
//
//void modify(int c, int l, int r, int rt) {
//    if (TRE.l == l && TRE.r == r) {
//        TRE.num = TRE.lazy = 1;
//        TRE.lc = TRE.rc = c;
//        return;
//    }
//    pushdown(rt);
//    int m = TRE.l + TRE.r >> 1;
//    if (r <= m)modify(c, l, r, rt << 1);
//    else if (l > m)modify(c, l, r, rt << 1 | 1);
//    else {
//        modify(c, l, m, rt << 1);
//        modify(c, m + 1, r, rt << 1 | 1);
//    }
//    pushup(rt);
//}
//
//int qry(int l, int r, int rt, int L, int R) {
//    if (TRE.l == L) LC = TRE.lc;
//    if (TRE.r == R) RC = TRE.rc;
//    if (TRE.l == l && TRE.r == r) return TRE.num;
//    pushdown(rt);
//    int m = TRE.l + TRE.r >> 1;
//    int ans;
//    if (r <= m) return qry(l, r, rt << 1, L, R);
//    else if (l > m)return qry(l, r, rt << 1 | 1, L, R);
//    else {
//        ans = qry(l, m, rt << 1, L, R) + qry(m + 1, r, rt << 1 | 1, L, R);
//        if (LS.rc == RS.rc)ans--;
//        return ans;
//    }
//    pushup(rt);
//}
//
//int query(int x, int y) {
//    int ans = 0;
//    int Lefcol = -1, Rigcol = -1;
//    while (top[x] != top[y]) {
//        if (dpt[top[x]] < dpt[top[y]])swap(x, y), swap(Lefcol, Rigcol);
//        ans += qry(nid[top[x]], nid[x], 1, nid[top[x]], nid[x]);
//        if (RC == Lefcol)ans--;
//        Lefcol = LC;
//        x = fa[top[x]];
//    }
//    if (dpt[x] < dpt[y])swap(x, y), swap(Lefcol, Rigcol);
//    ans += qry(nid[y], nid[x], 1, nid[y], nid[x]);
//    if (RC == Lefcol)ans--;
//    if (LC == Rigcol)ans--;
//    return ans;
//}
//
//void upd(int x, int y, int c) {
//    while (top[x] != top[y]) {
//        if (dpt[top[x]] < dpt[top[y]])swap(x, y);
//        modify(c, nid[top[x]], nid[x], 1);
//        x = fa[top[x]];
//    }
//    if (dpt[x] < dpt[y])swap(x, y);
//    modify(c, nid[y], nid[x], 1);
//}

int main(int argc, char const *argv[]) {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i <= n; ++i) {
        g[i].clear();
    }
    for (int i = 1; i <= n; ++i) {
        cin >> col[i];
    }
    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    t = 0;
    dfs1(1, 1);
    dfs2(1, 1);
    build(1, 1, n);
    for (int i = 1; i <= n; i++)
        update(1, pos[i], pos[i], col[i]);
    while (m--) {
        char opt;
        cin >> opt;
        if (opt == 'C') {
            int x, y, c;
            cin >> x >> y >> c;
            upd(x, y, c);
        } else {
            int x, y;
            cin >> x >> y;
            cout << solve(x, y) << endl;
        }
    }
    return 0;
}
