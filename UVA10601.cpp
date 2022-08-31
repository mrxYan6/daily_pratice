//
// Created by mrx on 2022/7/15.
//
#include <bits/stdc++.h>

using ll = long long;
std::vector<long long> fact(13);

void sol() {
    std::vector<int> a(12), cnt(7, 0);
    for (int i = 0; i < 12; ++i) {
        std::cin >> a[i];
        cnt[a[i]]++;
    }
    long long ans = fact[12];
    for (int i = 1; i <= 6; ++i) {
        ans /= fact[cnt[i]];
    }
    auto cacal = [&](int rep) {
        for (int i = 1; i <= 6; ++i) {
            if (cnt[i] % rep)return 0ll;
        }
        long long tmp = fact[12 / rep];
        for (int i = 1; i <= 6; ++i) {
            tmp /= fact[cnt[i] / rep];
        }
        return tmp;
    };
    //绕面心旋转90度或者270度，循环杰都是4
    ans += 6 * cacal(4);
    //绕面心旋转180度循环姐是2
    ans += 3 * cacal(2);
    //绕对角线旋转120度或者240度
    ans += 8 * cacal(3);
    //绕对边的中线旋转180
    for (int i = 1; i <= 6; ++i) {
        if (cnt[i] <= 0)continue;
        cnt[i]--;
        for (int j = 1; j <= 6; ++j) {
            if (cnt[j] <= 0)continue;
            cnt[j]--;
            ans += cacal(2);
            cnt[j]++;
        }
        cnt[i]++;
    }
    std::cout << ans / 24 << "\n";
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
    fact[0] = 1;
    for (int i = 1; i <= 12; ++i)fact[i] = fact[i - 1] * i;
    int n;
    std::cin >> n;
    while (n--)sol();
    return 0;
}