//
// Created by mrx on 2022/9/27.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>

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

const int mod = 1e9 + 7;
using Z = Modular<mod>;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;
	std::cin >> n;
	std::vector<std::vector<int>> G(n);
	for (int i = 1; i < n; ++i) {
		int x;
		std::cin >> x;
		G[i].push_back(x);
		G[x].push_back(i);
	}
	std::vector<int> color(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> color[i];
	}

	std::vector<std::array<Z, 2>> dp(n);
	std::function<void(int, int)> dfs = [&](int u, int fa) {
		dp[u][color[u]] = 1;
		for (auto v: G[u]) {
			if (v == fa)continue;
			dfs(v, u);
			dp[u][1] = dp[u][0] * dp[v][1] + dp[u][1] * (dp[v][1] + dp[v][0]);
			dp[u][0] = dp[u][0] * (dp[v][1] + dp[v][0]);
		}
	};


	dfs(0, -1);
//	for (int i = 0; i < n; ++i) {
//		std::cout << dp[i][0] << ' ' << dp[i][1] << '\n';
//	}
	std::cout << dp[0][1] << '\n';
	return 0;
}