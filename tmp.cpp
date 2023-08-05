#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    std::map<int, i64> a, b, c, d;
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        a[x + y]++;
        b[x - y]++;
        c[x]++;
        d[y]++;
    }

    i64 ans = 0;
    for (auto & t : {a, b, c, d}) {
        
        for (auto [_, c] : t) {
            ans += (c - 1) * c;
        }
    }

    std::cout << ans << '\n';
}

int main (){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}