//
// Created by mrx on 2022/7/10.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;
const int N = (1000000003) >> 6;
unsigned long long bitst[N + 10];
unsigned long long rep[66];

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif
    int n, s;
    std::cin >> n >> s;
    int limit = (n >> 6) + 1;
    while (s--) {
        int cur;
        std::cin >> cur;
        if (cur < 64) {
            memset(rep, 0, sizeof(rep));
            for (int i = 0; i < 64; ++i) {
                rep[(i * cur) >> 6] |= 1ull << ((i * cur) & 63);
            }
            for (int i = 0; i <= limit; i += cur)
                for (int j = 0; j < cur; ++j)
                    bitst[i + j] |= rep[j];
        } else {
            for (int i = 0; i < n; i += cur) {
                bitst[i >> 6] |= 1ull << (i & 63);
            }
        }
    }
    --limit;
    long long ans = 0;
    if ((n & 63) != 63) bitst[limit] &= (1ull << (n + 1 - (limit << 6))) - 1; //特判一下最后一块
    bitst[0] &= -2ull;
    for (int i = 0; i <= limit; ++i) ans += __builtin_popcountll(bitst[i] & (bitst[i] << 1) & (bitst[i] << 2));
    for (int i = 1; i <= limit; ++i) ans += __builtin_popcountll(bitst[i] & (bitst[i - 1] >> 62) & ((bitst[i - 1] >> 63) | (bitst[i] << 1)));
    cout << ans << endl;
    return 0;
}