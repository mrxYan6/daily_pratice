//
// Created by mrx on 2022/6/28.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;
const ll INF = 1e18;
vector<long long> I_2(1e5 + 100), I_1(1e5 + 100);

long long gcd(long long a, long long b) {
    return a % b == 0 ? b : gcd(b, a % b);
}

struct SegmentTree {
    struct Nod {
        ll l, r;
        ll suma, sumai, sumai2, tag1;

        Nod(long long l = 0, long long r = 0) : l(l), r(r), suma(0), sumai(0), sumai2(0), tag1(0) {}

        inline void apply(ll v, ll c = INF) {
            if (v != 0) {
                tag1 += v;
                suma += v * (r - l + 1);
                sumai += v * (I_1[r] - I_1[l - 1]);
                sumai2 += v * (I_2[r] - I_2[l - 1]);
            }
            if (c != INF) {
                tag1 = 0;
                suma = c * (r - l + 1);
                sumai = c * (I_1[r] - I_1[l - 1]);
                sumai2 = c * (I_2[r] - I_2[l - 1]);
            }
        }

    };

    //根据需要改变
    friend Nod merge(const Nod &lhs, const Nod &rhs) {
        Nod ans;
        ans.l = lhs.l, ans.r = rhs.r;
        ans.tag1 = 0;
        ans.suma = lhs.suma + rhs.suma;
        ans.sumai = lhs.sumai + rhs.sumai;
        ans.sumai2 = lhs.sumai2 + rhs.sumai2;
        return ans;
    }

    std::vector<Nod> tree;
    long long n;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define T tree[rt]
#define LS tree[rt<<1]
#define RS tree[rt<<1|1]

    inline void push_up(long long rt) {
        T = merge(LS, RS);
    }

    inline void push_down(long long rt) {
        if (T.tag1 != 0) {
            LS.apply(T.tag1);
            RS.apply(T.tag1);
            T.tag1 = 0;
        }
    }

    template<typename M>
    void build(long long l, long long r, long long rt, const std::vector<M> &base) {
        T.l = l, T.r = r, T.tag1 = 0;
        if (l == r) {
            T.apply(0, 0);
            return;
        }
        long long m = (l + r) >> 1;
        build(lson, base);
        build(rson, base);
        push_up(rt);
    }

    template<typename... M>
    void _modify(long long L, long long R, long long rt, const M &... v) {
        if (L <= T.l && T.r <= R) {
            if (T.l != T.r)push_down(rt);
            T.apply(v...);
            return;
        }
        long long m = (T.l + T.r) >> 1;
        push_down(rt);
        if (L <= m)_modify(L, R, rt << 1, v...);
        if (R > m)_modify(L, R, rt << 1 | 1, v...);
        push_up(rt);
    }

    Nod qry(long long L, long long R, long long rt) {
        if (L <= T.l && T.r <= R) {
            return T;
        }
        long long m = (T.l + T.r) >> 1;
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
    void modify(long long L, long long R, const M &...v) {
        assert(0 < L && L <= R && R <= n);
        _modify(L, R, 1, v...);
    }

    Nod query(long long L, long long R) {
        assert(0 < L && L <= R && R <= n);
        return qry(L, R, 1);
    }

    Nod query(long long pos) {
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
    long long n, m;
    cin >> n >> m;
    vector<long long> fact(n + 1000);
    for (long long i = 1; i <= n; ++i) {
        I_1[i] = I_1[i - 1] + i;
        I_2[i] = I_2[i - 1] + i * i;
    }
    vector<long long> cost(n, 0);
    SegmentTree SEG(cost);
    for (long long i = 0; i < m; ++i) {
        char opt;
        cin >> opt;
        if (opt == 'C') {
            long long l, r, v;
            cin >> l >> r >> v;
            if (l == r)continue;
            r--;
            SEG.modify(l, r, v);
        } else {
            long long l, r;
            cin >> l >> r;
            r--;
            auto x = SEG.query(l, r);
//            cerr << x.suma << ' ' << x.sumai << ' ' << x.sumai2 << endl;
            long long fz = x.suma * (r - l - l * r + 1) + x.sumai * (r + l) - x.sumai2;
            long long fm = (r - l + 1) * (r - l + 2) / 2;
            long long g = gcd(fz, fm);
            fz /= g, fm /= g;
            cout << fz << '/' << fm << endl;
        }
    }
    return 0;
}