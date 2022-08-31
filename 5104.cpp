//
// Created by mrx on 2022/6/26.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

const int mod = 1e9 + 7;

ll quickPow(ll base, ll fact) {
    ll ans = 1;
    while (fact) {
        if (fact & 1) ans = ans * base % mod;
        base = base * base % mod;
        fact >>= 1;
    }
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif
    ll w, n, k;
    cin >> w >> n >> k;
    cout << w * quickPow(quickPow(2, k), mod - 2) % mod << endl;
    return 0;
}