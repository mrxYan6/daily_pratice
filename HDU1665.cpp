//
// Created by mrx on 2022/10/18.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <numeric>
#include <cmath>
#include <functional>

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

using Pl = point<ll>;
using Ll = line<ll>;
using Pd = point<long double>;
using Ld = line<long double>;

bool isCross(Pd a, Pd b, Pd i, Pd j) {
	return sgn(cross(i - a, j - i)) * sgn(cross(i - b, j - i)) == -1 && sgn(cross(b - i, a - b)) * sgn(cross(b - j, a - b)) == -1;
}

bool onSeg(Pd a, Pd i, Pd j) {
	return sgn(cross(i - a, j - a)) == 0 && sgn(dot(a - i, a - j)) < 0;
}


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;
	int cas = 1;
	while (std::cin >> n && n) {
		std::vector<Pd> pod(n);
		std::vector<std::pair<Pd, Pd>> seg;
		for (int i = 0; i < n; ++i) {
			std::cin >> pod[i];
			if (i)seg.emplace_back(pod[i - 1], pod[i]);
		}
		for (int i = 0; i < n - 1; ++i) {
			for (int j = i + 1; j < n - 1; ++j) {
				if (isCross(seg[i].first, seg[i].second, seg[j].first, seg[j].second)) {
					pod.emplace_back(intersection(Ld(seg[i].first, seg[i].second), Ld(seg[j].first, seg[j].second)));
				}
			}
		}
		std::sort(pod.begin(), pod.end());
		pod.erase(std::unique(pod.begin(), pod.end()), pod.end());
		int Pcnt = pod.size();
		int Ecnt = n - 1;
		for (int i = 0; i < n - 1; ++i) {
			for (int j = 0; j < Pcnt; ++j) {
				if (onSeg(pod[j], seg[i].first, seg[i].second))Ecnt++;
			}
		}
		int ans = 2 + Ecnt - Pcnt;
		std::cout << "Case " << cas++ << ": There are " << ans << " pieces.\n";
	}
	return 0;
}