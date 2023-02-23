//
// Created by mrx on 2023/2/21.
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

const int P = 1e8;

template<class T>
T inverse(T a, T b) {
    T u = 0, v = 1;
    while (a != 0) {
        T t = b / a;
        b -= t * a;
        std::swap(a, b);
        u -= t * v;
        std::swap(u, v);
    }
    assert(b == 1);
    return u;
}

template<class T>
T power(T a, i64 b) {
    T ret = 1;
    for (; b; b >>= 1, a = a * a)if (b & 1)ret = ret * a;
    return ret;
}

int norm(int x) {
    return x < 0 ? x += P : x >= P ? x -= P : x;
}

struct ModInt {
    int a;

    ModInt(int a = 0) : a(norm(a)) {} // assume a <= 2P
    ModInt(i64 a) : a(norm(a % P)) {}

    int val() const { return a; }

    ModInt inv() const { return power(*this, P - 2); }

    ModInt operator -() const { return ModInt(norm(P - a)); }

    friend ModInt operator *(const ModInt& lhs, const ModInt& rhs) { return {i64(lhs.a) * rhs.a}; }

    friend ModInt operator +(const ModInt& lhs, const ModInt& rhs) { return {lhs.a + rhs.a}; }

    friend ModInt operator -(const ModInt& lhs, const ModInt& rhs) { return {lhs.a - rhs.a}; }

    friend ModInt operator /(const ModInt& lhs, const ModInt& rhs) { return {i64(lhs.a) * rhs.inv()}; }

    friend std::istream& operator >>(std::istream& is, ModInt& rhs) {
        i64 x;
        is >> x;
        rhs = ModInt(x);
        return is;
    }

    friend std::ostream& operator <<(std::ostream& os, const ModInt& rhs) { return os << rhs.val(); }
};

using Z = ModInt;
const int mod = 1e8;

void solve() {
    int n1, n2, k1, k2;
    std::cin >> n1 >> n2 >> k1 >> k2;
    int n = n1 + n2;
    std::vector dp(n + 1, std::vector(n1 + 1, std::vector<Z>(2)));
    dp[0][0][0] = 1;
    dp[0][0][1] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= n1 && j <= i; ++j) {
            //dp[i][j][0] += dp[i - len][j - len][1];
            //dp[i][j][1] += dp[i - len][j][0];
            int lmt1 = std::min(j, k1);
            for (int len = 1; len <= lmt1; ++len) {
                dp[i][j][0] = dp[i][j][0] + dp[i - len][j - len][1];
            }
            int lmt2 = std::min(i - j, k2);
            for (int len = 1; len <= lmt2; ++len) {
                dp[i][j][1] = dp[i][j][1] + dp[i - len][j][0];
            }
        }
    }
//    for (int i = 0; i <= n; ++i) {
//        for (int j = 0; j <= n1; ++j)std::cout << dp[i][j][0] << ' ';
//        std::cout << '\n';
//    }
//    std::cout << '\n';
//    for (int i = 0; i <= n; ++i) {
//        for (int j = 0; j <= n1; ++j)std::cout << dp[i][j][1] << ' ';
//        std::cout << '\n';
//    }
    std::cout << dp[n][n1][0] + dp[n][n1][1] << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}