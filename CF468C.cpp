//
// Created by mrx on 2022/7/15.
//
#include<bits/stdc++.h>

using ll = long long;

ll l, r, inf = 1e18, mod;

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#endif
    std::cin >> mod;
    l = mod - inf % mod * 9 % mod * 9 % mod;
    r = l + inf - 1;
    std::cout << l << ' ' << r << '\n';
    return 0;
}