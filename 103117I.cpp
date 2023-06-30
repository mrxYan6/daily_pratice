#include <iostream>
#include <vector>
#include <string>
#include <array>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    std::vector<std::array<int,3>> cnt (n + 1);
    for (int i = 1; i <= n; ++i) {
        cnt[i] = cnt[i - 1];
        cnt[i][a[i - 1] - 1]++; 
    }
    // std::cout << cnt[n][0] << '\n' << cnt[n][1] << '\n' << cnt[n][2] << '\n';
    int m;
    std::cin >> m;
    std::vector<i64> health(m);
    for (int i = 0; i < m; ++i) std::cin >> health[i];

    auto check = [&] (i64 x) {
        auto cur = health;
        i64 round = x / n;
        i64 remain = x % n;
        std::array<i64,3> num;
        for (int i = 0; i < 3; ++i) num[i] = cnt[n][i] * round + cnt[remain][i];

        for (int i = 0; i < m; ++i) {
            //6
            if (num[2] < 2) break;
            else {
                i64 ok = std::min(num[2] / 2, cur[i] / 6);
                num[2] -= ok * 2;
                cur[i] -= ok * 6;
            }
        }

        std::sort(cur.begin(), cur.end(), std::greater());
        for (int i = 0; i < m; ++i) {
            if (!num[2]) break;
            else {
                i64 ok = std::min(num[2], cur[i] / 3);
                num[2] -= ok;
                cur[i] -= ok * 3;
            }
        }
        
        std::sort(cur.begin(), cur.end(), std::greater());
        for (int i = 0; i < m; ++i) {
            if (!num[2]) break;
            if (cur[i]) {
                num[2]--;
                cur[i] -= std::min(cur[i], 3ll);
            }
        }

        std::sort(cur.begin(), cur.end(), std::greater());
        for (int i = 0; i < m; ++i) {
            if (!num[1]) break;
            else {
                i64 ok = std::min(num[1], cur[i] / 2);
                num[1] -= ok;
                cur[i] -= ok * 2;
            }
        }
        
        std::sort(cur.begin(), cur.end(), std::greater());
        for (int i = 0; i < m; ++i) {
            if (!num[1]) break;
            if (cur[i]) {
                num[1]--;
                cur[i] -= std::min(cur[i], 2ll);
            }
        }

        for (int i = 0;i < m; ++i) {
            if (!num[0]) break;
            if (cur[i]) {
                i64 ok = std::min(cur[i], num[0]);
                num[0] -= ok;
                cur[i] -= ok;
            }
        }

        bool ok = true;
        for (int i = 0; i < m; ++i) {
            if(cur[i]) ok = false;
        }
        return ok;
    };

    i64 l = 0, r = 1e14, ans = -1;
    while (l <= r) {
        i64 mid = (l + r) >> 1;
        if (check(mid)) {
            r = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
    }
    std::cout << ans << '\n';
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}