//
// Created by mrx on 2023/4/18.
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


struct node {
    int l, r, id;
};

void solve() {
    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i)std::cin >> a[i];
    std::vector<int> block(n);
    int m = std::sqrt(n);
    for (int i = 0; i < n; i++) {
        block[i] = i / m;
    }
    std::vector<node> s(q);
    for (int i = 0; i < q; ++i) {
        int l, r;
        std::cin >> l >> r;
        l--, r--;
        s[i].l = l, s[i].r = r, s[i].id = i;
    }
    std::sort(s.begin(), s.end(), [&](auto a, auto b) {
        return block[a.l] == block[b.l] ? ((block[a.l] & 1) ? a.r < b.r : a.r > b.r) : block[a.l] < block[b.l];
    });
    std::vector<i64> ans(q);

    std::vector<i64> cnt(*std::max_element(a.begin(), a.end()) + 1);
    i64 cur = 0;

    auto add = [&](int x) {
        cur -= 1ll * cnt[x] * cnt[x] * x;
        ++cnt[x];
        cur += 1ll * cnt[x] * cnt[x] * x;
    };

    auto del = [&](int x) {
        cur -= 1ll * cnt[x] * cnt[x] * x;
        --cnt[x];
        cur += 1ll * cnt[x] * cnt[x] * x;
    };

    int l = 0, r = -1;
    for (int i = 0; i < q; ++i) {
        while (l < s[i].l)del(a[l++]);
        while (l > s[i].l)add(a[--l]);
        while (r > s[i].r)del(a[r--]);
        while (r < s[i].r)add(a[++r]);
        ans[s[i].id] = cur;
    }
    for (int i = 0; i < q; ++i)std::cout << ans[i] << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();

    return 0;
}
