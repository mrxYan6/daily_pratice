//
// Created by mrx on 2022/6/1.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

struct LB {
    vector<long long> d, p;

    LB() {
        d.resize(60);
    }

    bool ins(long long x) {
        for (int i = 60; i >= 0; --i) {
            if (1 & (x >> i)) {
                if (!d[i]) {
                    d[i] = x;
                    break;
                }
                x ^= d[i];
            }
        }
        return x != 0;
    }

    void rebuild() {
        for (int i = 60; i >= 0; --i) {
            for (int j = i - 1; j >= 0; --j) {
                if (1 & (d[i] >> j)) {
                    d[i] ^= d[j];
                }
            }
        }
        for (int i = 0; i <= 60; ++i) {
            if (d[i])p.push_back(d[i]);
        }
    }

    int size() {
        return p.size();
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
    LB B;
    while (m--) {
        string s;
        cin >> s;
        long long tmp = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'O')tmp += (1LL << i);
        }
        B.ins(tmp);
    }
    B.rebuild();
    cout << (1ll << B.size()) % 2008 << endl;
    return 0;
}