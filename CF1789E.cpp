//
// Created by mrx on 2023/2/27.
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
    static Type norm(U& x) {
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
    Modular(const U& x) {
        value = norm(x);
    }

    const Type& operator ()() const {
        return value;
    }

    template<typename U>
    explicit operator U() const {
        return static_cast<U>(value);
    }

    Modular& operator +=(const Modular& other) {
        if ((value += other.value) >= Mod) value -= Mod;
        return *this;
    }

    Modular& operator -=(
            const Modular& other) {
        if ((value -= other.value) < 0) value += Mod;
        return *this;
    }

    template<typename U>
    Modular& operator +=(const U& other) { return *this += Modular(other); }

    template<typename U>
    Modular& operator -=(const U& other) { return *this -= Modular(other); }

    Modular& operator ++() { return *this += 1; }

    Modular& operator --() { return *this -= 1; }

    Modular operator ++(int) {
        Modular result(*this);
        *this += 1;
        return result;
    }

    Modular operator --(int) {
        Modular result(*this);
        *this -= 1;
        return result;
    }

    Modular operator -() const { return Modular(-value); }

    template<class ISTREAM_TYPE>
    friend ISTREAM_TYPE& operator >>(ISTREAM_TYPE& is, Modular& rhs) {
        ll v;
        is >> v;
        rhs = Modular(v);
        return is;
    }

    template<class OSTREAM_TYPE>
    friend OSTREAM_TYPE& operator <<(OSTREAM_TYPE& os, const Modular& rhs) {
        return os << rhs.val();
    }

    Modular& operator *=(const Modular& rhs) {
        value = ll(value) * rhs.value % Mod;
        return *this;
    }

    Modular& operator /=(const Modular& other) { return *this *= Modular(inverse(other.value, Mod)); }

    friend const Type& abs(const Modular& x) { return x.value; }

    friend bool operator ==(const Modular& lhs, const Modular& rhs) { return lhs.value == rhs.value; }

    friend bool operator <(const Modular& lhs, const Modular& rhs) { return lhs.value < rhs.value; }


    bool operator ==(const Modular& rhs) { return *this == rhs.value; }

    template<typename U>
    bool operator ==(U rhs) { return *this == Modular(rhs); }

    template<typename U>
    friend bool operator ==(U lhs, const Modular& rhs) { return Modular(lhs) == rhs; }

    bool operator !=(const Modular& rhs) { return *this != rhs; }

    template<typename U>
    bool operator !=(U rhs) { return *this != rhs; }

    template<typename U>
    friend bool operator !=(U lhs, const Modular& rhs) { return lhs != rhs; }

    bool operator <(const Modular& rhs) { return this->value < rhs.value; }

    Modular operator +(const Modular& rhs) { return Modular(*this) += rhs; }

    template<typename U>
    Modular operator +(U rhs) { return Modular(*this) += rhs; }

    template<typename U>
    friend Modular operator +(U lhs, const Modular& rhs) { return Modular(lhs) += rhs; }

    Modular operator -(const Modular& rhs) { return Modular(*this) -= rhs; }

    template<typename U>
    Modular operator -(U rhs) { return Modular(*this) -= rhs; }

    template<typename U>
    friend Modular operator -(U lhs, const Modular& rhs) { return Modular(lhs) -= rhs; }

    Modular operator *(const Modular& rhs) { return Modular(*this) *= rhs; }

    template<typename U>
    Modular operator *(U rhs) { return Modular(*this) *= rhs; }

    template<typename U>
    friend Modular operator *(U lhs, const Modular& rhs) { return Modular(lhs) *= rhs; }

    Modular operator /(const Modular& rhs) { return Modular(*this) /= rhs; }

    template<typename U>
    Modular operator /(U rhs) { return Modular(*this) /= rhs; }

    template<typename U>
    friend Modular operator /(U lhs, const Modular& rhs) { return Modular(lhs) /= rhs; }

private:
    Type value;
};

const int mod = 998244353;
using Z = Modular<mod>;

std::vector<int> prime, vis(1e7 + 10);

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::vector<int> exist(a[n - 1] + 1), pref(a[n - 1] + 1);
    for (int i = 0; i < n; ++i)exist[a[i]] = 1;
    for (int i = 1; i <= a[n - 1]; ++i)pref[i] = pref[i - 1] + exist[i];
    int sn = a[n - 1];

    Z ans = 0;
    for (int x = 1; x <= sn; ++x) {
        int l = sn / x, r = (sn + x - 1) / x;
        Z f = 0;
        if (l == r) {
            for (int i = l; i <= sn; i += l) {
                f += exist[i];
            }
        } else {
            for (int i = 1; i * l <= sn; i++) {
                if (i >= l) {
                    f += pref[sn] - pref[i * l - 1];
                    break;
                } else {
                    f += pref[std::min(sn, i * l + i)] - pref[i * l - 1];//u/x>=u%x->[kx,kx+k]
                }
            }
        }
        ans += x * f;
    }
    std::cout << ans << '\n';
}

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