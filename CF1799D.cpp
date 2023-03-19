//
// Created by mrx on 2023/3/4.
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
#include <cassert>

using i64 = long long;

const i64 INF = 1e18;

struct Nod {
    int l, r;
    i64 min, tag1, tag2;//tag1为加，tag2为改变

    Nod(int l = 0, int r = 0) : l(l), r(r), min(0), tag1(0), tag2(INF) {}

    inline void apply(i64 v1, i64 v2 = INF) {
        if (v2 != INF) {
            tag2 = v2;
            tag1 = 0;
            min = v2;
        }
        if (v1 != 0) {
            tag1 += v1;
            min += v1;
        }
    }

    //根据需要改变
    friend Nod merge(const Nod& lhs, const Nod& rhs) {
        Nod ans;
        ans.l = lhs.l, ans.r = rhs.r;
        ans.tag1 = 0, ans.tag2 = INF;
        ans.min = std::min(lhs.min, rhs.min);
        return ans;
    }

};


struct SegmentTree {
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
        if (T.tag1 != 0 || T.tag2 != INF) {
            LS.apply(T.tag1, T.tag2);
            RS.apply(T.tag1, T.tag2);
            T.tag1 = 0, T.tag2 = INF;
        }
    }

    template<typename M>
    void build(int l, int r, int rt, const std::vector<M>& base) {
        T.l = l, T.r = r, T.tag1 = 0, T.tag2 = INF;
        if (l == r) {
            T.apply(0, base[l]);
            return;
        }
        int m = (l + r) >> 1;
        build(lson, base);
        build(rson, base);
        push_up(rt);
    }

    template<typename... M>
    void _modify(int L, int R, int rt, const M& ... v) {
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
    SegmentTree(const std::vector<Type>& a) {
        n = a.size();
        tree.resize((n << 2) + 1);
        build(0, n - 1, 1, a);
    }

    template<typename... M>
    void modify(int L, int R, const M& ...v) {
        assert(0 <= L && L <= R && R <= n);
        _modify(L, R, 1, v...);
    }

    Nod query(int L, int R) {
        assert(0 <= L && L <= R && R <= n);
        return qry(L, R, 1);
    }

    Nod query(int pos) {
        assert(pos >= 0 && pos <= n);
        return qry(pos, pos, 1);
    }
};

void solve() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n + 1);
    std::vector<int> cold(k + 1), hot(k + 1);
    for (int i = 1; i <= n; ++i)std::cin >> a[i];
    for (int i = 1; i <= k; ++i)std::cin >> cold[i];
    for (int i = 1; i <= k; ++i)std::cin >> hot[i];

    std::vector<i64> d(k + 1, 0x3f3f3f3f3f3f3f3f);
    d[0] = 0;
    SegmentTree dp(d);
    for (int i = 1; i <= n; i++) {
        auto cur(a[i]), prev(a[i - 1]);
        auto nxt = dp.query(prev).min + (cur == prev ? hot[cur] : cold[cur]);
        nxt = std::min(nxt, dp.query(cur).min + hot[cur]);
        if (cur > 0)nxt = std::min(nxt, dp.query(0, cur - 1).min + cold[cur]);
        if (cur < k)nxt = std::min(nxt, dp.query(cur + 1, k).min + cold[cur]);
        dp.modify(0, k, cur == prev ? hot[cur] : cold[cur]);
        dp.modify(prev, prev, 0, nxt);
    }
    std::cout << dp.query(0, k).min << '\n';
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