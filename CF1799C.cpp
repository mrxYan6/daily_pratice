//
// Created by mrx on 2023/3/2.
//
#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <queue>
#include <array>
#include <map>

using i64 = long long;

void solve() {
    std::string s;
    std::cin >> s;
    int n = s.length();
    std::vector<int> cnt(26, 0);
    for (auto x: s)cnt[x - 'a']++;

    std::string ans(s.size(), ' ');
    int l = 0, r = n - 1;
    for (int i = 0; i < 26; ++i) {
        while (cnt[i] >= 2) {
            cnt[i] -= 2;
            ans[l++] = ans[r--] = 'a' + i;
        }
        if (cnt[i] == 1) {
            cnt[i]--;
            if (l == r) {
                ans[l] = 'a' + i;
            } else {
                int nx = i + 1;
                while (nx < 26 && cnt[nx] == 0)nx++;
                if (cnt[nx] == r - l) {
                    while (cnt[nx] >= 2) {
                        cnt[nx] -= 2;
                        ans[l++] = ans[r--] = nx + 'a';
                    }
                    if (cnt[nx] == 1) {
                        cnt[nx]--;
                        ans[l++] = nx + 'a';
                    }
                    ans[r] = i + 'a';
                } else {
                    while (nx < 26) {
                        while (cnt[nx] > 0)ans[l++] = nx + 'a', cnt[nx]--;
                        nx++;
                    }
                    ans[r] = i + 'a';
                }
            }
            break;
        }
    }
    std::cout << ans << '\n';
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}