#include <vector>
#include <iostream>

//c3,k -> c4,k
//c3,k -> c4,k
//c3,k -> c4,k
using i64 = long long;
const int mod = 998244353;
int main(){ 
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<i64> a(n);
    std::cin >> a[0];
    i64 x, y, m;
    std::cin >> x >> y >> m;
    for (int i = 1;i < n ; ++i) {
        a[i] = (a[i - 1] * x + y) % m;
    }
    int k;
    std::cin >> k;


    for (int i = 0; i <= k; ++i) {
        for (int j = 1; j < n; ++j) {
            a[j] = (a[j] + a[j - 1]) % mod;
        }
    }

    i64 ans = 0;
    for (int i = k - 1; i < n; ++i) {
        ans ^= 1ll * (i + 1) * a[i - k + 1];
    }
    std::cout << ans << '\n';
}