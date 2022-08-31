#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int N = 1e6 + 1000;
const int mod = 19930726;

ll qpow(ll a, ll b, ll m) {
    ll ans = 1;
    while (b) {
        if (b & 1) {
            ans = ans * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll n, m;
    cin >> n >> m;
    vector<int> d1(n), d2(n);
    vector<ll> cnt(n + 1, 0);
    string s;
    cin >> s;
    for (int i = 0, l = 0, r = -1; i < n; ++i) {
        int k = i > r ? 1 : min(d1[l + r - i], r - i + 1);
        while (k <= i && i + k < n && s[i - k] == s[i + k])k++;
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    for (int i = 0; i < n; ++i) {
        cnt[d1[i]]++;
    }
    ll ans = 1;
    ll sum = 0;
    for (ll i = n; i; i--) {
        sum += cnt[i];
        if (m == 0)break;
        ll b = min(sum, m);
        ans = ans * qpow(i * 2 - 1, b, mod) % mod;
        m -= b;
    }
    if (m != 0)ans = -1;
    cout << ans << endl;
}