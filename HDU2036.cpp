//
// Created by meiru on 2022/11/22.
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

int sgn(double x) {
	return x < -eps ? -1 : x > eps;
}

int sgn(i64 x) {
	return x < 0 ? -1 : x > 0;
}

template<typename T>
struct Point {
	T x, y;

	template<class Y>
	Point(const Point<Y>& cp):x(cp.x), y(cp.y) {}

	Point() : x(0), y(0) {}

	Point(T _x, T _y) : x(_x), y(_y) {}

	friend std::istream& operator >>(std::istream& is, Point& rhs) { return is >> rhs.x >> rhs.y; }

	friend std::ostream& operator <<(std::ostream& os, const Point& rhs) { return os << rhs.x << ' ' << rhs.y; }

	Point operator -(const Point& rhs) const { return {x - rhs.x, y - rhs.y}; }

	Point& operator -=(const Point& rhs) { return (*this) = (*this) - rhs; }

	Point operator +(const Point& rhs) const { return {x + rhs.x, y + rhs.y}; }

	Point& operator +=(const Point& rhs) { return (*this) = (*this) + rhs; }

	template<class Y>
	Point<double> operator *(const Y& rhs) const { return {x * rhs, y * rhs}; }

	template<class Y>
	Point<double> operator /(const Y& rhs) { return {x / rhs, y / rhs}; }

	friend double abs(const Point& lhs) { return std::sqrt(lhs.x * lhs.x + lhs.y * lhs.y); }

	friend i64 abs2(const Point& lhs) { return (lhs.x * lhs.x + lhs.y * lhs.y); }

	friend T cross(const Point& lhs, const Point& rhs) { return lhs.x * rhs.y - lhs.y * rhs.x; }

	friend T dot(const Point& lhs, const Point& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; }

	friend double angle(const Point& rhs) { return atan2(rhs.x, rhs.y); }

	Point rotate90() const { return {y, x}; }

	Point<double> rotate(double deg) { return {x * cos(deg) - y * sin(deg), x * sin(deg) + y * cos(deg)}; }

	bool operator <(const Point& rhs) const { return sgn(x - rhs.x) == 0 ? sgn(y - rhs.y) < 0 : sgn(x - rhs.x) < 0; }

	bool operator ==(const Point& rhs) const { return sgn(x - rhs.x) == 0 && sgn(y - rhs.y) == 0; }

	bool up() const { return sgn(y) == 0 ? sgn(x) >= 0 : sgn(y) > 0; }
};

using Pl = Point<i64>;
using Pd = Point<double>;

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

#include <iomanip>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	int n;
	while (std::cin >> n && n > 0) {
		std::vector<Pl> points(n);
		for (int i = 0; i < n; ++i)std::cin >> points[i];
		auto hull = ConvexHull(points);
		double ans = 0;
		int m = hull.size();
		for (int i = 1; i < m; ++i) {
			for (int j = i + 1; j < m; ++j) {
				for (int k = j + 1; k < m; ++k) {
					ans = std::max(ans, double(cross(hull[j] - hull[i], hull[k] - hull[i])) / 2);
				}
			}
		}
		std::cout << std::fixed << std::setprecision(2) << ans << '\n';
	}
	return 0;
}