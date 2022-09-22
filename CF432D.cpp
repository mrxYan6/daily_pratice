//
// Created by mrx on 2022/5/15.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

vector<int> getz(string &s) {
    int n = s.length();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r && z[i - l] < r - i + 1) {//如果i<=r
            z[i] = z[i - l];
        } else {
            z[i] = max(0, r - i + 1);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]])z[i]++;
        }
        if (i + z[i] - 1 > r)r = i + z[i] - 1, l = i;
    }
    return z;
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
    std::string s;
    std::cin >> s;
    int n = s.length();
    s = s + '#' + s;
    std::vector<int> z = getz(s);
    vector<int> sum(n + 1);
    for (int i = 1; i <= n; ++i) {
        sum[z[i + n]]++;
    }
    for (int i = n - 1; i >= 0; --i)sum[i] += sum[i + 1];
    vector<int> ans;
    for (int i = 1; i <= n; ++i) {
        if (z[i + n] == n - i + 1)ans.push_back(z[n + i]);
    }
    std::reverse(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (auto x: ans) {
        cout << x << ' ' << sum[x] << endl;
    }
    return 0;
}