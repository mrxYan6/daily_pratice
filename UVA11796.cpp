//
// Created by mrx on 2022/10/20.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <numeric>
#include <cmath>
#include <functional>
#include <complex>
#include <iomanip>

using ll = long long;


constexpr double eps = 1e-6;

template<typename T>
int sgn(T x) {
	return std::abs(x) < eps ? 0 : x < 0 ? -1 : 1;
}

template<typename T>
struct point {
	T x, y;

	point(T x, T y) : x(x), y(y) {}

	template<class Y>
	point(const point<Y>& cp):x(cp.x), y(cp.y) {}

	point() : x(0), y(0) {}

	friend std::istream& operator >>(std::istream& is, point& rhs) {
		return is >> rhs.x >> rhs.y;
	}

	friend std::ostream& operator <<(std::ostream& os, const point& rhs) {
		return os << rhs.x << ' ' << rhs.y;
	}

	point& operator +=(const point& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	point operator +(const point& rhs) const {
		point ans(*this);
		return ans += rhs;
	}

	point& operator -=(const point& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	point operator -(const point& rhs) const {
		point ans(*this);
		return ans -= rhs;
	}

	template<class Y>
	point<Y> operator *(const Y& rhs) const {
		return point<Y>(x * rhs, y * rhs);
	}

	template<class Y>
	point<Y> operator /(const Y& rhs) {
		return point<Y>(x / rhs, y / rhs);
	}

	friend double abs(const point& lhs) {
		return std::sqrt(lhs.x * lhs.x + lhs.y * lhs.y);
	}

	friend T cross(const point& lhs, const point& rhs) {
		return lhs.x * rhs.y - lhs.y * rhs.x;
	}

	friend T dot(const point& lhs, const point& rhs) {
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}

	bool operator <(const point& rhs) const {
		return x == rhs.x ? y < rhs.y : x < rhs.x;
	}


	bool operator ==(const point& rhs) const {
		return std::abs(x - rhs.x) <= eps && std::abs(y - rhs.y) <= eps;
	}
};

template<typename T>
point<long double> Rotate(point<T> a, double deg) { return {a.x * cos(deg) - a.y * sin(deg), a.x * sin(deg) + a.y * cos(deg)}; }

template<typename T>
struct line {
	point<T> a, dir;

	line(const point<T>& a, const point<T>& b) : a(a), dir(b - a) {}

	template<class Y>
	line(const point<Y>& cp) : a(cp.a), dir(cp.dir) {}

	friend point<long double> intersection(const line<T> lhs, const line<T> rhs) {
		long double t = (long double) cross(rhs.a - lhs.a, rhs.dir) / cross(lhs.dir, rhs.dir);
		return lhs.dir * t + point<double>(lhs.a);
	}

	double dis(const point<T>& rhs) {
		return std::abs(cross(rhs - a, dir)) / dir.abs();
	}

	line rotate(double deg) {
		line<long double> ans(*this);
		ans.dir = Rotate(dir, deg);
		return ans;
	}
};

using Pd = point<double>;
using Ld = line<double>;

bool isCross(Pd a, Pd b, Pd i, Pd j) {
	return sgn(cross(i - a, j - i)) * sgn(cross(i - b, j - i)) == -1 && sgn(cross(b - i, a - b)) * sgn(cross(b - j, a - b)) == -1;
}

bool onSeg(Pd a, Pd i, Pd j) {
	return sgn(cross(i - a, j - a)) == 0 && sgn(dot(a - i, a - j)) < 0;
}

void sol() {
	int a, b;
	std::cin >> a >> b;
	std::vector<Pd> pa(a), pb(b);
	for (int i = 0; i < a; ++i)std::cin >> pa[i];
	for (int i = 0; i < b; ++i)std::cin >> pb[i];


	double totLenA = 0, totLenB = 0;
	for (int i = 1; i < a; ++i)totLenA += abs(pa[i] - pa[i - 1]);
	for (int i = 1; i < b; ++i)totLenB += abs(pb[i] - pb[i - 1]);

	int ptr_a = 1, ptr_b = 1;
	double min = 1e9, max = -1e9;
	Pd poa = pa[0], pob = pb[0];
	for (; ptr_a < a && ptr_b < b;) {
		double lenA = abs(pa[ptr_a] - poa);
		double lenB = abs(pb[ptr_b] - pob);
		double time = std::min(lenA / totLenA, lenB / totLenB);
		Pd dA = (pa[ptr_a] - poa) * time * totLenA / lenA;
		Pd dB = (pb[ptr_b] - pob) * time * totLenB / lenB;
		auto cacal = [&](Pd o, Pd l, Pd r) {
			max = std::max({abs(o - l), abs(o - r), max});
			if (l == r) {
				min = std::min(min, abs(o - r));
			} else {
				if (sgn(dot(l - o, r - l)) > 0) {
					min = std::min(min, abs(o - l));
				} else if (sgn(dot(r - o, r - l)) < 0) {
					min = std::min(min, abs(o - r));
				} else {
					min = std::min(min, std::abs(cross(o - l, r - l) / abs(l - r)));
				}
			}
		};
		cacal(poa, pob, pob + dB - dA);

		poa = poa + dA;
		pob = pob + dB;
		if (poa == pa[ptr_a])ptr_a++;
		if (pob == pb[ptr_b])ptr_b++;
	}

	std::cout << std::fixed << std::setprecision(0) << max - min << '\n';
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int t;
	std::cin >> t;
	for (int i = 1; i <= t; ++i) {
		std::cout << "Case " << i << ": ";
		sol();
	}

	return 0;
}