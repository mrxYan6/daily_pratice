#include <bits/stdc++.h>

using namespace std;
#define ll long long
const int N = 50000 + 1000;

ll a[N], cnt[N];
ll now;

struct nod {
    ll l, r, id;

    nod(ll a, ll b, ll c) : l(a), r(b), id(c) {}
};

ll gcd(ll A, ll B) {
    if (B == 0)return A;
    else return gcd(B, A % B);
}

inline void add(ll pos) {
    now += cnt[a[pos]];
    cnt[a[pos]]++;
}

inline void del(ll pos) {
    cnt[a[pos]]--;
    now -= cnt[a[pos]];
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
    ll n, m;
    cin >> n >> m;
    for (ll i = 1; i <= n; ++i) {
        cin >> a[i];
        cnt[a[i]] = 0;
    }
    vector<pair<ll, ll>> ans(m + 1);
    vector<nod> p;
    for (ll i = 1; i <= m; ++i) {
        ll l, r;
        cin >> l >> r;
        p.emplace_back(l, r, i);
    }
    ll block = ceil(sqrt(n));
    sort(p.begin(), p.end(), [&](nod &a, nod &b) {
        return a.l / block ^ b.l / block ? a.l / block < b.l / block : a.r < b.r;
    });
    ll l = 1, r = 0;
    now = 0;
    for (auto x: p) {
        ll lb = x.l, rb = x.r;
        while (l < lb)del(l++);
        while (l > lb)add(--l);
        while (r < rb)add(++r);
        while (r > rb)del(r--);
        ll len = x.r - x.l + 1;
        ans[x.id] = make_pair(now, len * (len - 1) / 2);
    }
    for (ll i = 1; i <= m; ++i) {
        if (ans[i].first == 0 && ans[i].second == 0)cout << "0/1" << endl;
        else {
            ll g = gcd(ans[i].first, ans[i].second);
            cout << ans[i].first / g << '/' << ans[i].second / g << endl;
        }
    }
    return 0;
}