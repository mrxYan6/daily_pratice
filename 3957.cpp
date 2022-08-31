//
// Created by mrx on 2022/5/21.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif
    int n, d, k;
    cin >> n >> d >> k;
    vector<pair<ll, ll>> a(n);
    vector<ll> dp(n);
    auto check = [&](ll m) -> bool {
        ll lef = max(d - m, 1ll), rig = d + m;
        deque<ll> q;
        std::fill(dp.begin(), dp.end(), -INF);
        for (int i = 0; i < n; ++i) {
            if (a[i].first > rig)break;
            if (a[i].first < lef)continue;
            dp[i] = a[i].second;
        }
        int ptr = 0;
        for (int i = 0; i < n; ++i) {
            while (!q.empty() && a[q.front()].first < a[i].first - rig)q.pop_front();
            while (a[ptr].first <= a[i].first - lef) {
                ptr++;
                if (dp[ptr - 1] == -INF)continue;
                if (a[ptr - 1].first < a[i].first - rig)continue;
                while (!q.empty() && dp[q.back()] <= dp[ptr - 1])q.pop_back();
                q.push_back(ptr - 1);
            }
            if (!q.empty())dp[i] = max(dp[i], dp[q.front()] + a[i].second);
            if (dp[i] >= k)return true;
        }
        return false;
    };
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
    }
    ll l = 0, r = 1e9 + 100, ans = -1;
    while (l <= r) {
        ll m = (l + r) >> 1;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else l = m + 1;
    }
    cout << ans << endl;
    return 0;
}