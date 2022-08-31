//
// Created by mrx on 2022/5/22.
//

#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

struct edge {
    int u, v, w;

    edge(int u, int v, int w) : u(u), v(v), w(w) {}

    bool operator<(const edge &rhs) const {
        return w > rhs.w;
    }
};

const ll INF = 1e18;

struct SegmentTree {
    struct Nod {
        int l, r;
        ll ans, tag2;//tag1为加，tag2为改变

        Nod(int l = 0, int r = 0) : l(l), r(r), ans(0), tag2(INF) {}

        inline void apply(ll v2) {
            if (v2 != INF) {
                tag2 = v2;
                ans = v2;
            }
        }

    };

    //根据需要改变
    friend Nod merge(const Nod &lhs, const Nod &rhs) {
        Nod ans;
        ans.l = lhs.l, ans.r = rhs.r;
        ans.tag2 = INF;
        ans.ans = std::min(lhs.ans, rhs.ans);
        return ans;
    }

    std::vector<Nod> tree;
    int n;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define T tree[rt]
#define LS tree[rt<<1]
#define RS tree[rt<<1|1]

    inline void push_up(int rt) {
        T = merge(LS, RS);
    }

    inline void push_down(int rt) {
        if (T.tag2 != INF) {
            LS.apply(T.tag2);
            RS.apply(T.tag2);
            T.tag2 = INF;
        }
    }

    template<typename M>
    void build(int l, int r, int rt, const std::vector<M> &base) {
        T.l = l, T.r = r, T.tag2 = INF;
        if (l == r) {
            T.apply(base[l]);
            return;
        }
        int m = (l + r) >> 1;
        build(lson, base);
        build(rson, base);
        push_up(rt);
    }

    template<typename... M>
    void _modify(int L, int R, int rt, const M &... v) {
        if (L <= T.l && T.r <= R) {
            if (T.l != T.r)push_down(rt);
            T.apply(v...);
            return;
        }
        int m = (T.l + T.r) >> 1;
        push_down(rt);
        if (L <= m)_modify(L, R, rt << 1, v...);
        if (R > m)_modify(L, R, rt << 1 | 1, v...);
        push_up(rt);
    }

    Nod qry(int L, int R, int rt) {
        if (L <= T.l && T.r <= R) {
            return T;
        }
        int m = (T.l + T.r) >> 1;
        Nod res;
        push_down(rt);
        if (R <= m)res = qry(L, R, rt << 1);
        else if (L > m)res = qry(L, R, rt << 1 | 1);
        else res = merge(qry(L, R, rt << 1), qry(L, R, rt << 1 | 1));
        push_up(rt);
        return res;
    }

#undef lson
#undef rson
#undef T
#undef LS
#undef RS

    template<class Type>
    SegmentTree(const std::vector<Type> &a) {
        n = a.size();
        n--;
        tree.resize((n << 2) + 1);
        build(1, n, 1, a);
    }

    template<typename... M>
    void modify(int L, int R, const M &...v) {
        assert(0 < L && L <= R && R <= n);
        _modify(L, R, 1, v...);
    }

    Nod query(int L, int R) {
        assert(0 < L && L <= R && R <= n);
        return qry(L, R, 1);
    }

    Nod query(int pos) {
        assert(pos > 0 && pos <= n);
        return qry(pos, pos, 1);
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
    int n, m;
    cin >> n >> m;
    vector<edge> e;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        e.emplace_back(u, v, w);
    }
    std::sort(e.begin(), e.end());
    vector<int> DSU(n + 1);
    for (int i = 1; i <= n; ++i)DSU[i] = i;
    std::function<int(int)> DSU_find = [&](int x) -> int {
        return DSU[x] == x ? x : DSU[x] = DSU_find(DSU[x]);
    };
    std::function<void(int, int)> DSU_merge = [&](int x, int y) -> void {
        if (DSU_find(x) != DSU_find(y))DSU[DSU_find(x)] = DSU_find(y);
    };

    vector<vector<pair<int, int>>> G(n + 1, vector<pair<int, int>>());
    for (auto edg: e) {
        if (DSU_find(edg.u) != DSU_find(edg.v)) {
            DSU_merge(edg.u, edg.v);
            G[edg.u].emplace_back(edg.v, edg.w);
            G[edg.v].emplace_back(edg.u, edg.w);
        }
    }
    vector<int> son(n + 1), top(n + 1), siz(n + 1), dpt(n + 1), f(n + 1), id(n + 1, 0);
    int cnt = 0;
    std::function<void(int, int)> dfs1 = [&](int u, int fa) {
        dpt[u] = dpt[fa] + 1, siz[u] = 1, son[u] = 0, f[u] = fa;
        for (auto v: G[u]) {
            if (v.first == fa)continue;
            dfs1(v.first, u);
            siz[u] += siz[v.first];
            if (siz[v.first] > siz[son[u]])son[u] = v.first;
        }
    };
    vector<int> a(n + 1);
    int w = 1e9;
    std::function<void(int, int)> dfs2 = [&](int x, int topx) {
        top[x] = topx;
        id[x] = ++cnt;
        a[cnt] = w;
        if (son[x]) {
            for (auto v: G[x])if (v.first == son[x])w = v.second;
            dfs2(son[x], son[x]);
        }
        for (auto v: G[x]) {
            if (v.first == f[x] || v.first == son[x])continue;
            w = v.second;
            dfs2(v.first, v.first);
        }
    };
    cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (id[i] == 0) {
            dfs1(i, i);
            dfs2(i, i);
        }
    }
    SegmentTree seg(a);
    std::function<ll(int, int)> ans = [&](int x, int y) -> ll {
        if (DSU_find(x) != DSU_find(y))return -1;
        else {
            ll ans = INF;
            while (top[x] != top[y]) {
                if (id[top[x]] < id[top[y]])swap(x, y);
                ans = min(ans, seg.query(id[x], id[top[x]]).ans);
                x = f[top[x]];
            }
            if (x == y)return ans;
            if (dpt[x] > dpt[y])swap(x, y);
            ans = min(ans, seg.query(id[x] + 1, id[y]).ans);
            return ans;
        }
    };
    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        cout << ans(x, y) << endl;
    }
    return 0;
}