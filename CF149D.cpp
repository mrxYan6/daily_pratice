//
// Created by mrx on 2022/8/9.
//
#include <bits/stdc++.h>

using ll = long long;

template<typename T>
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

template<typename T>
T power(T a, int b) {
    T ans = 1;
    for (; b; a *= a, b >>= 1) {
        if (b & 1)ans *= a;
    }
    return ans;
}

template<int Mod>
class Modular {
public:
    using Type = int;

    template<typename U>
    static Type norm(U &x) {
        Type v;
        if (-Mod <= x && x < Mod) v = static_cast<Type>(x);
        else v = static_cast<Type>(x % Mod);
        if (v < 0) v += Mod;
        return v;
    }

    constexpr Modular() : value() {}

    int val() const { return value; }

    Modular inv() const {
        return Modular(inverse(value, Mod));
    }

    template<typename U>
    Modular(const U &x) {
        value = norm(x);
    }

    const Type &operator()() const {
        return value;
    }

    template<typename U>
    explicit operator U() const {
        return static_cast<U>(value);
    }

    Modular &operator+=(const Modular &other) {
        if ((value += other.value) >= Mod) value -= Mod;
        return *this;
    }

    Modular &operator-=(
            const Modular &other) {
        if ((value -= other.value) < 0) value += Mod;
        return *this;
    }

    template<typename U>
    Modular &operator+=(const U &other) { return *this += Modular(other); }

    template<typename U>
    Modular &operator-=(const U &other) { return *this -= Modular(other); }

    Modular &operator++() { return *this += 1; }

    Modular &operator--() { return *this -= 1; }

    Modular operator++(int) {
        Modular result(*this);
        *this += 1;
        return result;
    }

    Modular operator--(int) {
        Modular result(*this);
        *this -= 1;
        return result;
    }

    Modular operator-() const { return Modular(-value); }

    template<class ISTREAM_TYPE>
    friend ISTREAM_TYPE &operator>>(ISTREAM_TYPE &is, Modular &rhs) {
        ll v;
        is >> v;
        rhs = Modular(v);
        return is;
    }

    template<class OSTREAM_TYPE>
    friend OSTREAM_TYPE &operator<<(OSTREAM_TYPE &os, const Modular &rhs) {
        return os << rhs.val();
    }

    Modular &operator*=(const Modular &rhs) {
        value = ll(value) * rhs.value % Mod;
        return *this;
    }

    Modular &operator/=(const Modular &other) { return *this *= Modular(inverse(other.value, Mod)); }

    friend const Type &abs(const Modular &x) { return x.value; }

    friend bool operator==(const Modular &lhs, const Modular &rhs) { return lhs.x == rhs.x; }

    friend bool operator<(const Modular &lhs, const Modular &rhs) { return lhs.x < rhs.x; }


    bool operator==(const Modular &rhs) { return *this == rhs.value; }

    template<typename U>
    bool operator==(U rhs) { return *this == Modular(rhs); }

    template<typename U>
    friend bool operator==(U lhs, const Modular &rhs) { return Modular(lhs) == rhs; }

    bool operator!=(const Modular &rhs) { return *this != rhs; }

    template<typename U>
    bool operator!=(U rhs) { return *this != rhs; }

    template<typename U>
    friend bool operator!=(U lhs, const Modular &rhs) { return lhs != rhs; }

    bool operator<(const Modular &rhs) { return this->value < rhs.value; }

    Modular operator+(const Modular &rhs) { return Modular(*this) += rhs; }

    template<typename U>
    Modular operator+(U rhs) { return Modular(*this) += rhs; }

    template<typename U>
    friend Modular operator+(U lhs, const Modular &rhs) { return Modular(lhs) += rhs; }

    Modular operator-(const Modular &rhs) { return Modular(*this) -= rhs; }

    template<typename U>
    Modular operator-(U rhs) { return Modular(*this) -= rhs; }

    template<typename U>
    friend Modular operator-(U lhs, const Modular &rhs) { return Modular(lhs) -= rhs; }

    Modular operator*(const Modular &rhs) { return Modular(*this) *= rhs; }

    template<typename U>
    Modular operator*(U rhs) { return Modular(*this) *= rhs; }

    template<typename U>
    friend Modular operator*(U lhs, const Modular &rhs) { return Modular(lhs) *= rhs; }

    Modular operator/(const Modular &rhs) { return Modular(*this) /= rhs; }

    template<typename U>
    Modular operator/(U rhs) { return Modular(*this) /= rhs; }

    template<typename U>
    friend Modular operator/(U lhs, const Modular &rhs) { return Modular(lhs) /= rhs; }

private:
    Type value;
};

constexpr int mod = 1e9 + 7;
using Z = Modular<mod>;

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
    std::cin >> s;
    int n = s.length();
    std::vector<int> match(n);
    std::stack<int> stk;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '(')stk.push(i);
        else {
            match[i] = stk.top();
            match[stk.top()] = i;
            stk.pop();
        }
    }

    std::vector<std::vector<std::vector<std::vector<Z>>>> dp(n + 1, std::vector<std::vector<std::vector<Z>>>(n + 1, std::vector<std::vector<Z>>(4, std::vector<Z>(4))));
    std::function<void(int, int)> dfs = [&](int l, int r) {
        if (l + 1 == r) {
            dp[l][r][0][1] = dp[l][r][0][2] = dp[l][r][1][0] = dp[l][r][2][0] = 1;
        } else if (r == match[l]) {
            dfs(l + 1, r - 1);
            for (int l_color = 0; l_color < 3; ++l_color) {
                for (int r_color = 0; r_color < 3; ++r_color) {
                    if (r_color != 1) dp[l][r][0][1] += dp[l + 1][r - 1][l_color][r_color];
                    if (r_color != 2) dp[l][r][0][2] += dp[l + 1][r - 1][l_color][r_color];
                    if (l_color != 1) dp[l][r][1][0] += dp[l + 1][r - 1][l_color][r_color];
                    if (l_color != 2) dp[l][r][2][0] += dp[l + 1][r - 1][l_color][r_color];
                }
            }
        } else {
            dfs(l, match[l]);
            dfs(match[l] + 1, r);
            for (int ll_color = 0; ll_color < 3; ++ll_color) {
                for (int lr_color = 0; lr_color < 3; ++lr_color) {
                    for (int rl_color = 0; rl_color < 3; rl_color++) {
                        for (int rr_color = 0; rr_color < 3; rr_color++) {
                            if (lr_color == rl_color && lr_color != 0)continue;
                            dp[l][r][ll_color][rr_color] += dp[l][match[l]][ll_color][lr_color] * dp[match[l] + 1][r][rl_color][rr_color];
                        }
                    }
                }
            }
        }
    };

    dfs(0, n - 1);
    Z ans = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            ans += dp[0][n - 1][i][j];
        }
    }
    std::cout << ans << '\n';
    return 0;
}