#include <bits/stdc++.h>

using ll = long long;

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#endif
    std::string s;
    std::map<char, int> mp;
    mp['a'] = 1;
    mp['e'] = 1;
    mp['i'] = 1;
    mp['o'] = 1;
    mp['u'] = 1;
    mp['y'] = 1;
    std::cin >> s;
    int n = s.length();
    std::vector<int> sum(n + 1);
    std::vector<int> ansi(n + 1);
    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i - 1] + mp[s[i - 1]];
    }
    for (int i = 1; i <= n; ++i) {
        ansi[i] = ansi[i - 1] + sum[n - i + 1] - sum[i - 1];
    }
    double ans = 0;
    for (int i = 1; i <= n; ++i)ans += 1.0 * ansi[i] / i;
    ans /= (n * (n + 1) / 2);
    std::cout << std::fixed << std::setprecision(12) << ans << '\n';
    return 0;
}