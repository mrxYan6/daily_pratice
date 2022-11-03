//
// Created by mrx on 2022/10/31.
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
#include <iomanip>

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

template<typename T>
struct Line {
	Point<T> a, v;

	Line(const Point<T>& a, const Point<T>& b) : a(a), v(b - a) {}

	template<class Y>
	Line(const Point<Y>& cp) : a(cp.a), v(cp.v) {}

	Pd point(double t) {
		return a + v * t;
	}

	friend Point<long double> intersection(const Line<T> lhs, const Line<T> rhs) {
		long double t = (long double) cross(rhs.a - lhs.a, rhs.v) / cross(lhs.v, rhs.v);
		return lhs.v * t + Point<double>(lhs.a);
	}

	double dis(const Point<T>& rhs) {
		return std::abs(cross(rhs - a, v)) / v.abs();
	}

	Line rotate(double deg) {
		Line<long double> ans(*this);
		ans.v = Rotate(v, deg);
		return ans;
	}
};

using Ll = Line<i64>;
using Ld = Line<double>;

bool isCross(Pd a, Pd b, Pd i, Pd j) {
	return sgn(cross(i - a, j - i)) * sgn(cross(i - b, j - i)) == -1 && sgn(cross(b - i, a - b)) * sgn(cross(b - j, a - b)) == -1;
}

bool onSeg(Pd a, Pd i, Pd j) {
	return sgn(cross(i - a, j - a)) == 0 && sgn(dot(a - i, a - j)) < 0;
}

std::vector<Pl> ConvexHull(std::vector<Pl> points) {
	int n = points.size();
	std::sort(points.begin(), points.end());
	std::deque<Pl> dq;

	for (auto& point: points) {
		while (dq.size() > 1 && sgn(cross(dq[dq.size() - 1] - dq[dq.size() - 2], point - dq[dq.size() - 2])) <= 0)dq.pop_back();
		dq.push_back(point);
	}

	int k = int(dq.size());
	for (int i = n - 1; i >= 0; i--) {
		while (dq.size() > k && sgn(cross(dq[dq.size() - 1] - dq[dq.size() - 2], points[i] - dq[dq.size() - 2])) <= 0)dq.pop_back();
		dq.push_back(points[i]);
	}

	std::vector<Pl> ans(dq.begin(), dq.end());
	return ans;
}

std::array<i64, 3> getNorm(Ll l) {
	return {l.v.y, -l.v.x, -l.a.x * l.v.y + l.v.x * l.a.y};
}

void sol() {
	int n;
	std::cin >> n;
	std::vector<Pl> points(n);
	for (int i = 0; i < n; ++i)std::cin >> points[i];
	i64 sumX = 0, sumY = 0;
	for (int i = 0; i < n; ++i) {
		sumX += points[i].x;
		sumY += points[i].y;
	}

	if (n > 1) {
		std::vector<Pl> hull = ConvexHull(points);
//	for (auto x: hull)std::cerr << x << '\n';

		double ans = 2e18;
		int m = hull.size();
		for (int i = 1; i < m; ++i) {
//		std::cerr << hull[i - 1] << ' ' << hull[i] << '\n';
			Ll line(hull[i - 1], hull[i]);
			auto coefficient = getNorm(line);
			double fm = abs(Pl(coefficient[0], coefficient[1]));
//		for (auto x: coefficient)std::cerr << x << ' ';
//		std::cerr << '\n';
			i64 fz = std::abs(coefficient[0] * sumX + coefficient[1] * sumY + n * coefficient[2]);
			ans = std::min(ans, fz / fm);
		}

		std::cout << std::fixed << std::setprecision(3) << ans / n << '\n';
	} else std::cout << "0.000\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	int t;
	std::cin >> t;
	for (int cas = 1; cas <= t; ++cas) {
		std::cout << "Case #" << cas << ": ";
		sol();
	}
	return 0;
}