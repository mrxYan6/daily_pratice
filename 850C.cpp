#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <numeric>
#include <queue>
#include <map>
#include <functional>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }


    std::map<int, int> mp;
    mp[0] = 0;
    std::function<int(int)> sg = [&] (int x) {
        if (mp.count(x)) {
            return mp[x];
        }
        std::map<int, int> cnt;

        for (int i = 1; i < 31; ++i) {
            if (x >> i) {
                cnt[sg((x >> i) | (x & ((1 << i) - 1)))] = 1;
            } else break;
        }

        int mex = 0;
        while (cnt[mex]) ++mex;

        return mp[x] = mex;
    };

    int ans = 0;
    int mx = *std::max_element(a.begin(), a.end());
    for (int k = 2; k * k <= mx; ++k) {
        int S = 0;
        for (int i = 0; i < n; ++i) {
            int cnt = 0;
            int& tmp = a[i];
            while (tmp % k == 0) {
                tmp /= k;
                ++cnt;
            }
            S |= (1 << cnt);
        }

        // std::cout << k << ' ' << S << '\n';
        ans ^= sg(S);
    }

    std::sort(a.begin(), a.end());
    a.erase(std::unique(a.begin(), a.end()), a.end());
    for (int x : a) {
        if (x == 1)continue;
        ans ^= 1;
    }

    if (ans) std::cout << "Mojtaba\n";
    else std::cout << "Arpa\n";
} 

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();

    return 0;
}