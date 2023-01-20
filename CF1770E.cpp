//
// Created by meiru on 2023/1/19.
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
#include <cassert>

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

using Z = Modular<998244353>;

void solve() {
	int n, k;
	std::cin >> n >> k;
	std::vector<int> a(k);
	std::vector<Z> P(n);

	for (auto& x: a) {
		std::cin >> x;
		x--;
		P[x] = 1;
	}
	std::vector<std::vector<int>> g(n);

	std::vector<int> u(n - 1), v(n - 1);
	for (int i = 0; i < n - 1; ++i) {
		std::cin >> u[i] >> v[i];
		u[i]--, v[i]--;
		g[u[i]].emplace_back(v[i]);
		g[v[i]].emplace_back(u[i]);
	}


	std::vector<Z> sum(n);
	std::vector<int> fa(n);
	std::function<void(int, int)> dfs = [&](int u, int p) {
		sum[u] = P[u];
		for (auto v: g[u]) {
			if (v == p)continue;
			dfs(v, u);
			fa[v] = u;
			sum[u] += sum[v];
		}
	};

	dfs(0, -1);

	Z ans = 0;
	for (int i = 0; i < n - 1; ++i) {
		if (fa[u[i]] == v[i]) std::swap(u[i], v[i]);
		Z puv = P[u[i]] * (1 - P[v[i]]);
		Z pvu = P[v[i]] * (1 - P[u[i]]);
		Z delta = -puv * sum[v[i]] * (k - sum[v[i]]) - pvu * sum[v[i]] * (k - sum[v[i]]);
		delta += puv * (sum[v[i]] + 1) * (k - sum[v[i]] - 1) + pvu * (sum[v[i]] - 1) * (k - sum[v[i]] + 1);
		ans = (ans + sum[v[i]] * (k - sum[v[i]]) + delta / 2);
		P[u[i]] = P[v[i]] = (P[u[i]] + P[v[i]]) / 2;
	}
	std::cout << ans / Z(1ll * k * (k - 1) / 2) << '\n';
}


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	solve();

	return 0;
}