//
// Created by mrx on 2022/7/20.
//
#include <bits/stdc++.h>

using ll = long long;

void sol() {
    ll n;
    std::cin >> n;
    std::cout << (12 * n * n * n + 8 * n * n + 3 * n * n * n * n + n * n * n * n * n * n) / 24 << std::endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#endif
    int t;
    std::cin >> t;
    while (t--)sol();
    return 0;
}