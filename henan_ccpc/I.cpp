#include <vector>
#include <iostream>
#include <array>
#include <numeric>

using i64 = long long;

template <typename T>
struct Fen {
    const int n;
    std::vector<T> a;

    Fen (int n) : n(n), a(n + 1) {}

    void add(int pos, int x) {
        for (int i = pos; i <= n; i += i & -i) {
            a[i] += x;
        }
    }

    T query(int x) {
        T res = 0;
        for (int i = x; i; i -= i & -i) {
            res += a[i];
        }
        return res;
    }

    T query(int l, int r) {
        if (l == 0 || l > r) {
            return 0;
        }
        return query(r) - query(l - 1);
    }
};


void solve() {
    int n;
    std::cin >> n;
    std::vector<int> x1(n), x2(n), y1(n), y2(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
    }

    std::vector<std::array<int,4>> lists;

    for (int i = 0; i < n; ++i) {
        lists.push_back({x1[i],x2[i],y1[i],1});
        lists.push_back({x1[i],x2[i],y2[i],-1});
    }

    std::sort(lists.begin(), lists.end(), [&](auto i,auto j) {
        return i[2] < j[2];
    });

    i64 notok = 0;
    Fen<i64> f(2 * n + 1);
    for (auto [l,r,pos,val] : lists) {
        i64 cur = f.query(1,2 * n + 1) - f.query(l,r) + r - l + 1;
        f.add(l, val);
        f.add(r, val);
        // std::cout << "!" << pos << ' ' << l << ' ' << r << ' ' << cur << ' ' << val << '\n';
        notok += cur;
    }
    std::cout << 1ll * (2 * n) * (2 * n) - notok << '\n';
}

int main () {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    solve();

    return 0;
}