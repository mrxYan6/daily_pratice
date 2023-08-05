#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <numeric>
#include <queue>
#include <map>
#include <functional>
#include <complex>
#include <cassert>


using i64 = long long;

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

template<typename T>
T power(T a, int b, int mod) {
    T ans = 1;
    for (; b; a = a * a % mod, b >>= 1) {
        if (b & 1)ans = ans * a % mod;
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

    i64 val() const { return value; }

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
        i64 v;
        is >> v;
        rhs = Modular(v);
        return is;
    }

    template<class OSTREAM_TYPE>
    friend OSTREAM_TYPE &operator<<(OSTREAM_TYPE &os, const Modular &rhs) {
        return os << rhs.val();
    }

    Modular &operator*=(const Modular &rhs) {
        value = i64(value) * rhs.value % Mod;
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
const int P = 7340033;

using Z = Modular<P>;

std::vector<int> rev;
std::vector<Z> roots{0, 1};

void dft(std::vector<Z>& a) {
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
		while ((1 << k) < n) {
			Z e = power(Z(3), (P - 1) >> (k + 1));
			for (int i = 1 << (k - 1); i < (1 << k); i++) {
				roots[i << 1] = roots[i];
				roots[i << 1 | 1] = roots[i] * e;
			}
			k++;
		}
	}

	for (int k = 1; k < n; k *= 2) {
		for (int i = 0; i < n; i += 2 * k) {
			for (int j = 0; j < k; j++) {
				Z u = a[i + j];
				Z v = a[i + j + k] * roots[k + j];
				a[i + j] = u + v;
				a[i + j + k] = u - v;
			}
		}
	}
}

void idft(std::vector<Z>& a) {
	int n = a.size();
	std::reverse(a.begin() + 1, a.end());
	dft(a);
}

struct Poly : public std::vector<Z> {
	using std::vector<Z>::vector;

	Poly() = default;

	explicit Poly(const std::vector<Z>& a) : vector(a) {}

	Z operator [](int idx) const {
		if (idx < size()) {
			return *(this->begin() + idx);
		} else {
			return 0;
		}
	}

	Z& operator [](int idx) {
		return *(this->begin() + idx);
	}

	friend Poly operator +(const Poly& a, const Poly& b) {
		Poly res(std::max(a.size(), b.size()));
		for (int i = 0; i < int(res.size()); i++) {
			res[i] = a[i] + b[i];
		}
		return res;
	}

	friend Poly operator -(const Poly& a, const Poly& b) {
		Poly res(std::max(a.size(), b.size()));
		for (int i = 0; i < int(res.size()); i++) {
			res[i] = a[i] - b[i];
		}

		return res;
	}

	friend Poly operator *(Poly a, Poly b) {
		if (a.empty() || b.empty()) {
			return {};
		}
		int sz = 1, tot = a.size() + b.size() - 1;
		while (sz < tot) {
			sz *= 2;
		}
		a.resize(sz), b.resize(sz);
		dft(a), dft(b);
		Z inv = (1 - P) / sz;
		for (int i = 0; i < sz; ++i) {
			a[i] = a[i] * b[i];
			a[i] = a[i] * inv;
		}
		idft(a);
		return Poly(a).modxk(tot);
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

	Poly operator <<(const int k) const {
		auto b = *this;
		b.insert(b.begin(), k, 0);
		return b;
	}

	Poly operator >>(const int k) const {
		if (size() <= k) {
			return {};
		}
		return Poly(begin() + k, end());
	}

	Poly mulxk(int k) const {
		return *this << k;
	}

	Poly modxk(int k) const {
		k = std::min(k, (int) size());
		return Poly(begin(), begin() + k);
	}

	Poly divxk(int k) const {
		if (size() <= k) {
			return {};
		}
		return Poly(begin() + k, end());
	}


	Poly deriv() const {
		if (empty()) {
			return {};
		}
		Poly res(size() - 1);
		for (int i = 0; i < size() - 1; ++i) {
			res[i] = (i + 1) * (*this)[i + 1];
		}
		return res;
	}

	Poly integr() const {
		Poly res(size() + 1);
		for (int i = 0; i < size(); ++i) {
			res[i + 1] = (*this)[i] / (i + 1);
		}
		return res;
	}

	Poly inv(int m) const {
		Poly x{(*this)[0].inv()};
		int k = 1;
		while (k < m) {
			k *= 2;
			x = (x * (Poly{2} - modxk(k) * x)).modxk(k);
		}
		return x.modxk(m);
	}

	Poly log(int m) const {
		return (deriv() * inv(m)).integr().modxk(m);
	}

	Poly exp(int m) const {
		Poly x{Z(1)};
		int k = 1;
		while (k < m) {
			k *= 2;
			x = (x * (Poly{Z(1)} - x.log(k) + modxk(k))).modxk(k);
		}
		return x.modxk(m);
	}

	Poly pow(int k, int m) const {
		int i = 0;
		while (i < size() && (*this)[i].val() == 0) {
			i++;
		}
		if (i == size() || 1LL * i * k >= m) {
			return Poly(m);
		}
		Z v = (*this)[i];
		Poly f = divxk(i) * (v.inv().val());
		return (f.log(m - i * k) * k).exp(m - i * k).mulxk(i * k) * power(v, k).val();
	}

	Poly sqrt(int m) const {
		Poly x{Z(1)};
		int k = 1;
		while (k < m) {
			k *= 2;
			x = (x + (modxk(k) * x.inv(k)).modxk(k)) * ((P + 1) / 2);
		}
		return x.modxk(m);
	}

	Poly mulT(Poly b) const {
		if (b.empty()) {
			return {};
		}
		int n = b.size();
		std::reverse(b.begin(), b.end());
		return ((*this) * b).divxk(n - 1);
	}

	std::vector<Z> eval(std::vector<Z> x) const {
		if (empty()) {
			return Poly(x.size());
		}
		const int n = std::max(int(x.size()), (int) size());
		std::vector<Poly> q(4 * n);
		std::vector<Z> ans(x.size());
		x.resize(n);
		std::function<void(int, int, int)> build = [&](int p, int l, int r) {
			if (r - l == 1) {
				q[p] = Poly{1, -x[l]};
			} else {
				int m = (l + r) / 2;
				build(2 * p, l, m);
				build(2 * p + 1, m, r);
				q[p] = q[2 * p] * q[2 * p + 1];
			}
		};
		build(1, 0, n);
		std::function<void(int, int, int, const Poly&)> work = [&](int p, int l, int r, const Poly& num) {
			if (r - l == 1) {
				if (l < int(ans.size())) {
					ans[l] = num[0];
				}
			} else {
				int m = (l + r) / 2;
				work(2 * p, l, m, num.mulT(q[2 * p + 1]).modxk(m - l));
				work(2 * p + 1, m, r, num.mulT(q[2 * p]).modxk(r - m));
			}
		};
		work(1, 0, n, mulT(q[1].inv(n)));
		return ans;
	}
};

std::map<int, Poly> mem;

Poly& solve(int x) {
    if (mem.count(x)) return mem[x];
    auto& cur = mem[x];
    if (x == 0) return cur = Poly{1};
    auto f = solve(x - 1);
    auto tmp = f * f;
    return cur = ((tmp * tmp).mulxk(1) + Poly{1}).modxk(1001);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        int n, k;
        std::cin >> n >> k;

        int cnt = 0;
        while ((n & 1) && (n != 1)) {
            n /= 2;
            cnt++;
        }
        // std::cout << n << ' ' << cnt << '\n';
        auto& x = solve(cnt);
        // for (auto t : x) std::cout << t << ' ';
        // std::cout << '\n';
        if (k >= x.size()) {
            std::cout << 0 << '\n';
        } else {
            std::cout << x[k] << '\n';
        }
    }

    return 0;
}