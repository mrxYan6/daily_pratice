//
// Created by mrx on 2022/6/3.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

struct LinearBasis {
    std::vector<long long> p, d;
    int cnt;

    LinearBasis() {
        p.clear();
        d.clear();
        d.resize(40, 0);
        cnt = 0;
    }

    bool ins(long long x) {
        for (int i = 40; i >= 0; --i) {
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
};

LinearBasis merge(const LinearBasis &lhs, const LinearBasis &rhs) {
    LinearBasis ans = lhs;
    for (int i = 40; i >= 0; --i) {
        if (rhs.d[i]) {
            ans.ins(rhs.d[i]);
        }
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
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)cin >> a[i];
    std::sort(a.begin(), a.end(), greater());
    ll ans = 0;
    LinearBasis l;
    for (int i = 0; i < n; ++i) {
        if (l.ins(a[i]))continue;
        else ans += a[i];
    }
    if (ans) cout << ans << endl;
    else cout << ans << endl;
    return 0;
}