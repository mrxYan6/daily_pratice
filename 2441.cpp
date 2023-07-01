#include <vector>
#include <iostream>
#include <numeric>

void solve() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)std::cin >> a[i];

    std::vector<int> father(n + 1);
    for (int i = 1; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        father[y] = x;
    }

    while (k--) {
        int op;
        std::cin >> op;
        if (op == 1) {
            // std::cout << "!1 :";
            int x;
            std::cin >> x;
            int v = a[x];
            x = father[x];
            int ans = -1;
            while (x != 0) {
                if (std::gcd(v, a[x]) != 1) {
                    ans = x;
                    break;
                }
                x = father[x];
            }
            std::cout << ans << '\n';
        } else {
            // std::cout << "!2 :";

            int p, v;
            std::cin >> p >> v;
            a[p] = v;
        }
    }

}

int main () {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();

    return 0;
}