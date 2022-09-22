//
// Created by mrx on 2022/9/14.
//
#include <bits/stdc++.h>

using ll = long long;

template<typename T>
T power(T a, ll b) {
	T ans = 1;
	for (; b; a *= a, b >>= 1) {
		if (b & 1)ans *= a;
	}
	return ans;
}

template<typename T>
T inverse(T a, ll b) {
	return power(a, b - 2);
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

	const Type& operator()() const {
		return value;
	}

	template<typename U>
	explicit operator U() const {
		return static_cast<U>(value);
	}

	Modular& operator+=(const Modular& other) {
		if ((value += other.value) >= Mod) value -= Mod;
		return *this;
	}

	Modular& operator-=(
			const Modular& other) {
		if ((value -= other.value) < 0) value += Mod;
		return *this;
	}

	template<typename U>
	Modular& operator+=(const U& other) { return *this += Modular(other); }

	template<typename U>
	Modular& operator-=(const U& other) { return *this -= Modular(other); }

	Modular& operator++() { return *this += 1; }

	Modular& operator--() { return *this -= 1; }

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
	friend ISTREAM_TYPE& operator>>(ISTREAM_TYPE& is, Modular& rhs) {
		ll v;
		is >> v;
		rhs = Modular(v);
		return is;
	}

	template<class OSTREAM_TYPE>
	friend OSTREAM_TYPE& operator<<(OSTREAM_TYPE& os, const Modular& rhs) {
		return os << rhs.val();
	}

	Modular& operator*=(const Modular& rhs) {
		value = ll(value) * rhs.value % Mod;
		return *this;
	}

	Modular& operator/=(const Modular& other) { return *this *= Modular(inverse(other, Mod)); }

	friend const Type& abs(const Modular& x) { return x.value; }


	friend bool operator<(const Modular& lhs, const Modular& rhs) { return lhs.value < rhs.value; }


	bool operator==(const Modular& rhs) { return this->value == rhs.value; }

	template<typename U>
	bool operator==(U rhs) const { return *this == Modular(rhs); }

	template<typename U>
	friend bool operator==(U lhs, const Modular& rhs) { return Modular(lhs) == rhs; }

	bool operator!=(const Modular& rhs) { return *this != rhs; }

	template<typename U>
	bool operator!=(U rhs) { return *this != rhs; }

	template<typename U>
	friend bool operator!=(U lhs, const Modular& rhs) { return lhs != rhs; }

	bool operator<(const Modular& rhs) { return this->value < rhs.value; }

	Modular operator+(const Modular& rhs) { return Modular(*this) += rhs; }

	template<typename U>
	Modular operator+(U rhs) { return Modular(*this) += rhs; }

	template<typename U>
	friend Modular operator+(U lhs, const Modular& rhs) { return Modular(lhs) += rhs; }

	Modular operator-(const Modular& rhs) { return Modular(*this) -= rhs; }

	template<typename U>
	Modular operator-(U rhs) { return Modular(*this) -= rhs; }

	template<typename U>
	friend Modular operator-(U lhs, const Modular& rhs) { return Modular(lhs) -= rhs; }

	Modular operator*(const Modular& rhs) { return Modular(*this) *= rhs; }

	template<typename U>
	Modular operator*(U rhs) { return Modular(*this) *= rhs; }

	template<typename U>
	friend Modular operator*(U lhs, const Modular& rhs) { return Modular(lhs) *= rhs; }

	Modular operator/(const Modular& rhs) { return Modular(*this) /= rhs; }

	template<typename U>
	Modular operator/(U rhs) { return Modular(*this) /= rhs; }

	template<typename U>
	friend Modular operator/(U lhs, const Modular& rhs) { return Modular(lhs) /= rhs; }

private:
	Type value;
};

constexpr int mod = 1e8 + 7;
using Z = Modular<mod>;

ll bsgs(Z a, Z b) {
	std::map<Z, int> hash;
	ll m = std::sqrt(mod) + 0.5;
	Z cur = 1;
	Z inv = 1 / power(a, m);
	hash[cur] = 0;
	for (int i = 1; i < m; ++i) {
		cur *= a;
		if (!hash.count(cur))hash[cur] = i;
	}

	for (int i = 0; i < m; ++i) {
		if (hash.count(b))return i * m + hash[b];
		b *= inv;
	}
	return -1;
}

int main() {
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
#endif
#ifndef LOCAL
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
#endif
	int t;
	std::cin >> t;
	for (int cas = 1; cas <= t; ++cas) {
		std::cout << "Case " << cas << ": ";
		ll n, k, b;
		Z r;
		std::cin >> n >> k >> b >> r;
		std::vector<ll> x(b), y(b);
		std::set<std::pair<ll, ll>> ban;
		ll m = 1;
		for (int i = 0; i < b; ++i) {
			std::cin >> x[i] >> y[i];
			m = std::max(x[i], m);
			ban.emplace(x[i], y[i]);
		}

		ll cnt = n;
		for (int i = 0; i < b; ++i) {
			if (x[i] != m && !ban.count({x[i] + 1, y[i]}))cnt++;
			if (x[i] == 1)cnt--;
		}
		Z p = power(Z(k), cnt);
		p *= power(Z(k - 1), 1ll * n * m - b - cnt);

		if (r == p) {
			std::cout << m << '\n';
		} else {
			cnt = 0;
			for (int i = 0; i < b; ++i) if (x[i] == m)cnt++;
			m++;
			p *= power(Z(k), cnt) * power(Z(k - 1), n - cnt);

			if (p == r) std::cout << m << '\n';
			else {
				std::cout << bsgs(power(Z(k - 1), n), r / p) + m << '\n';
			}
		}
	}
	return 0;
}