
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <array>
#include <stack>
#include <cassert>
#include <functional>
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

constexpr int mod = 998244353;
const int p = mod;
using Z = Modular<mod>;

std::vector<int> rev;
std::vector<Z> roots{0, 1};

void dft(std::vector<Z> & a) {
    int n = a.size();

    if (int(rev.size()) != n) {
        rev.resize(n);
        for (int i = 0; i < n; ++i) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (rev[i] < i)std::swap(a[i], a[rev[i]]);
    }

    if (int(roots.size() < n)) {
        int k = __builtin_ctz(roots.size());

        roots.resize(n);
        while((1 << k) < n) {
            Z e = power(Z(3), (p - 1) >> (k + 1));

            for (int i = 1 << (k - 1); i < (1 << k); ++i) {
                roots[i << 1] = roots[i];
                roots[i << 1 | 1] = roots[i] * e;
            }
            k ++;
        }
    }

    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += k * 2) {
            for (int j = 0; j < k; ++j) {
                Z u = a[i + j];
                Z v = a[i + j + k] * roots[j + k];
                a[i + j] = u + v;
                a[i + j + k] = u - v;
            }
        }
    }
}

void idft(std::vector<Z> &a) {
    int n = a.size();
    std::reverse(a.begin() + 1, a.end());
    dft(a);
}

struct Poly : public std::vector<Z> {
    using std::vector<Z>::vector;

    Poly() = default;

    explicit Poly(const std::vector<Z> &a) : vector(a){}

    Z operator [] (int i) const {
        if(i < size()) {
            return *(this->begin() + i);
        } else {
            return 0;
        }
    }

    Z& operator [](int i) {
        return *(this->begin() + i);
    }

    friend Poly operator + (const Poly & a, const Poly & b){
        Poly ret(std::max(a.size(), b.size()));
        for (int i = 0; i < ret.size(); ++i) {
            ret[i] = a[i] + b[i];
        }
        return ret;
    }



    friend Poly operator - (const Poly & a, const Poly & b){
        Poly ret(std::max(a.size(), b.size()));
        for (int i = 0; i < ret.size(); ++i) {
            ret[i] = a[i] - b[i];
        }
        return ret;
    }

    Poly modxk(int k) const {
        k = std::min(k, int(size()));
        return Poly(begin(), begin() + k);
    }

    friend Poly operator * (Poly a, Poly b){
        if(a.empty() || b.empty()) return {};

        int sz = 1, tot  = a.size() + b.size() - 1;
        while(sz < tot) sz <<= 1;
        a.resize(sz), b.resize(sz);
        dft(a), dft(b);
        Z inv = (1 - p) / Z(sz);
        for (int i = 0; i < sz; ++i) {
            a[i] = a[i] * b[i] * inv;
        }
        idft(a);
        return Poly(a).modxk(tot);
    } 

    Poly inv(int m) const {
        Poly x{(*this)[0].inv()};
        int k = 1;
        while(k < m) {
            k <<= 1;
            x = (x * (Poly{2} - modxk(k) * x)).modxk(k);
        }
        return x.modxk(m);
    }

    friend Poly operator *(int a, Poly b) {
		for (int i = 0; i < int(b.size()); i++) {
			b[i] = b[i] * a;
		}
		return b;
	}

    friend Poly operator *(Poly a, int b) {
		for (int i = 0; i < int(a.size()); i++) {
			a[i] = a[i] * b;
		}
		return a;
	}

    Poly integr() const{
        Poly res(size() + 1);
        for (int i = 0; i < size(); ++i) {
            res[i + 1] = (*this)[i] / Z(i + 1);
        }
        return res;
    }

    Poly deriv() const {
        if(empty()) return {};
        Poly res(size() - 1);
        for (int i = 0;i < size() - 1; ++i) {
            res[i] = (*this)[i + 1] * Z(i + 1);
        }
        return res;
    }

    Poly log(int m) const{
        return (deriv() * inv(m)).integr().modxk(m);
    }
    
    Poly exp(int m) const {
        Poly x{Z(1)};
        int k = 1;
        while (k < m){
            k <<= 1;
            x = (x * (Poly{Z(1)} - x.log(k) + modxk(k))).modxk(k);
        }
        return x.modxk(m);
    }


    Poly divxk(int k) const {
        if(size() <= k) return {};
        return Poly(begin() + k,  end());
    }

    Poly mulxk(int k) const {
        auto b = *this;
        b.insert(b.begin(), k, Z(0));
        return b;
    }

    Poly pow(int k, int m)const {
        int i = 0;
        while (i < size() && (*this)[i].val() == 0) {
            ++i;
        }
        if (i == size() || 1ll * i * k >= m) {
            return Poly(m);
        }

        Z v = (*this)[i];
        Poly f = divxk(i) * (v.inv().val());
        return (f.log(m - i * k) * k).exp(m - i * k).mulxk(i * k) * power(v,k).val();
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<Poly> blacks(n, Poly(2, 1));
    std::vector<Poly> whites(m, Poly(2, 1));
    for (int i = 0; i < n; ++i) blacks[i][1] = i + 1;
    for (int i = 0; i < m; ++i) whites[i][1] = -(i + 1);
    std::function<Poly(int,int,std::vector<Poly>&)> Mult = [&] (int l, int r, std::vector<Poly>& base) -> Poly {
        if (l == r) return base[l];
        int mid = (l + r) >> 1;
        return Mult(l, mid,base) * Mult(mid + 1, r,base).modxk(n + 1);
    };

    auto a = Mult(0, n - 1, blacks);
    auto b = Mult(0, m - 1, whites);
    b = b.inv(n + 1);
    Z white = b[n];
    Z black = 0;
    for (int i = n - k; i <= n; ++i) {
        black = black + a[i];
    }
    std::cout << white * black << '\n';
    return 0;
}