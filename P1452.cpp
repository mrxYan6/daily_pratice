//
// Created by mrx on 2022/11/3.
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

	friend std::ostream& operator <<(std::ostream& os, const Point& rhs) { return os << '(' << rhs.x << ',' << rhs.y << ')'; }

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
	std::sort(points.begin(), points.end());
	points.erase(std::unique(points.begin(), points.end()), points.end());
	int n = points.size();
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

i64 rotateCalipers(std::vector<Pl>& hull) {
	i64 d = 0;
	int n = hull.size();
	n--;
	if (n == 2)return abs2(hull[0] - hull[1]);
	int j = 2;
	for (int i = 0; i < n; ++i) {
		while (cross(hull[i + 1] - hull[i], hull[j] - hull[i]) < cross(hull[i + 1] - hull[i], hull[j + 1] - hull[i]))j = j < n - 1 ? j + 1 : 0;
//		std::cout << j << "!\n";
		d = std::max({d, abs2(hull[i] - hull[j]), abs2(hull[i + 1] - hull[j])});
//		std::cout << d << '\n';
	}
	return d;
}

int dx[] = {1, 1, 0, 0};
int dy[] = {0, 1, 1, 0};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int t;
	std::cin>>t;
	while (t--) {
		int n;
		std::cin >> n;
		std::vector<Pl> points;
//		for (int i = 0; i < n; ++i)std::cin >> points[i];
		for (int i = 0; i < n; ++i) {
			Pl ld;
			std::cin >> ld;
			i64 d;
			std::cin >> d;
			for (int j = 0; j < 4; ++j)points.emplace_back(ld.x + d * dx[j], ld.y + d * dy[j]);
		}
		auto hull = ConvexHull(points);
		i64 ans = rotateCalipers(hull);
		std::cout << ans << '\n';
	}
	return 0;
}