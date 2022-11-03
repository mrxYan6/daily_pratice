//
// Created by meiru on 2022/10/31.
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

constexpr double eps = 1e-6;

template<typename T>
int sgn(T x) {
	return std::abs(x) < eps ? 0 : x < 0 ? -1 : 1;
}

template<typename T>
struct Point {
	T x, y;

	Point(T x, T y) : x(x), y(y) {}

	bool up() const {
		return y == 0 ? x >= 0 : y > 0;
	}

	template<class Y>
	Point(const Point<Y>& cp):x(cp.x), y(cp.y) {}

	Point() : x(0), y(0) {}

	friend std::istream& operator >>(std::istream& is, Point& rhs) {
		return is >> rhs.x >> rhs.y;
	}

	friend std::ostream& operator <<(std::ostream& os, const Point& rhs) {
		return os << rhs.x << ' ' << rhs.y;
	}

	Point& operator +=(const Point& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Point operator +(const Point& rhs) const {
		Point ans(*this);
		return ans += rhs;
	}

	Point& operator -=(const Point& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Point operator -(const Point& rhs) const {
		Point ans(*this);
		return ans -= rhs;
	}

	template<class Y>
	Point<Y> operator *(const Y& rhs) const {
		return Point<Y>(x * rhs, y * rhs);
	}

	template<class Y>
	Point<Y> operator /(const Y& rhs) {
		return Point<Y>(x / rhs, y / rhs);
	}

	Point rotate90() const {
		return {y, x};
	}

	Point<double> rotate(double deg) {
		return {x * cos(deg) - y * sin(deg), x * sin(deg) + y * cos(deg)};
	}

	friend double abs(const Point& lhs) {
		return std::sqrt(lhs.x * lhs.x + lhs.y * lhs.y);
	}

	friend T cross(const Point& lhs, const Point& rhs) {
		return lhs.x * rhs.y - lhs.y * rhs.x;
	}

	friend T dot(const Point& lhs, const Point& rhs) {
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}

	bool operator <(const Point& rhs) const {
		return x == rhs.x ? y < rhs.y : x < rhs.x;
	}

	friend double angle(const Point& rhs) {
		return atan2(rhs.x, rhs.y);
	}

	bool operator ==(const Point& rhs) const {
		return std::abs(x - rhs.x) <= eps && std::abs(y - rhs.y) <= eps;
	}
};

template<typename T>
Point<long double> Rotate(Point<T> a, double deg) { return {a.x * cos(deg) - a.y * sin(deg), a.x * sin(deg) + a.y * cos(deg)}; }

using Pl = Point<i64>;
using Pd = Point<double>;

void sol() {
	int n;
	std::cin >> n;
	std::vector<Pl> points(n);
	for (int i = 0; i < n; ++i)std::cin >> points[i];	std::sort(points.begin(), points.end(), [&](Pl a, Pl b) {
		return a.up() ^ b.up() ? a.up() > b.up() : cross(a, b) > 0;
	});

//	for (auto x: points)std::cout << x << '\n';
//	std::cout << '\n';
	int ans = 0;
	int l, r;
	l = r = 0;
	for (; l < n; ++l) {
		auto cmp = [](Pl a, Pl b) {
			return cross(a, b) == 0 ? dot(a, b) > 0 : cross(a, b) > 0;
		};
		while (cmp(points[l], points[r])) {
			r = (r + 1) % n;
			if (l == r) {
				std::cout << 0 << '\n';
				return;
			}
		}
		ans = std::max(ans, (n + r - l) % n);
	}

	std::cout << n - ans << '\n';
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	int t;
	std::cin >> t;
	while (t--) {
		sol();
	}
	return 0;
}

