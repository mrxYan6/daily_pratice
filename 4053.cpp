//
// Created by mrx on 2022/5/23.
//

#include <bits/stdc++.h>

#define ll long long
#define endl '\n'

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
    std::cin >> n;
    std::vector<std::pair<ll, ll>> a(n);

    for (ll i = 0; i < n; ++i) {
        std::cin >> a[i].first >> a[i].second;
    }

    std::sort(a.begin(), a.end(), [&](std::pair<ll, ll> &lhs, std::pair<ll, ll> &rhs) {
        return lhs.second < rhs.second;
    });
    std::priority_queue<ll> q;

    ll cur = 0, ans = 0;
    for (int i = 0; i < n; ++i) {
        if (cur + a[i].first > a[i].second) {
            if (a[i].first < q.top()) {
                cur -= q.top();
                q.pop();
                q.push(a[i].first);
                cur += a[i].first;
            }
        } else {
            q.push(a[i].first);
            ans++;
            cur += a[i].first;
        }
    }

    std::cout << ans << endl;
    return 0;
}