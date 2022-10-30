//
// Created by mrx on 2022/10/30.
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

using Pd = Point<double>;
using Ld = Line<double>;

bool isCross(Pd a, Pd b, Pd i, Pd j) {
	return sgn(cross(i - a, j - i)) * sgn(cross(i - b, j - i)) == -1 && sgn(cross(b - i, a - b)) * sgn(cross(b - j, a - b)) == -1;
}

bool onSeg(Pd a, Pd i, Pd j) {
	return sgn(cross(i - a, j - a)) == 0 && sgn(dot(a - i, a - j)) < 0;
}

int dx[] = {1, 1, -1, -1};
int dy[] = {1, -1, 1, -1};

std::vector<Pd> ConvexHull(std::vector<Pd> points) {
	int n = points.size();
	std::sort(points.begin(), points.end());
	std::deque<Pd> dq;

	for (auto& point: points) {
		while (dq.size() > 1 && sgn(cross(dq[dq.size() - 1] - dq[dq.size() - 2], point - dq[dq.size() - 2])) <= 0)dq.pop_back();
		dq.push_back(point);
	}

	int k = int(dq.size());
	for (int i = n - 1; i >= 0; i--) {
		while (dq.size() > k && sgn(cross(dq[dq.size() - 1] - dq[dq.size() - 2], points[i] - dq[dq.size() - 2])) <= 0)dq.pop_back();
		dq.push_back(points[i]);
	}

	std::vector<Pd> ans(dq.begin(), dq.end());
	return ans;
}

void sol() {
	int n;
	std::cin >> n;

	std::vector<Pd> points;
	double fz = 0;
	for (int i = 0; i < n; ++i) {
		double x, y, w, h, phi;
		std::cin >> x >> y >> w >> h >> phi;
		fz += w * h;
		Pd cent(x, y);
		for (int j = 0; j < 4; ++j) {
			Pd vertex = cent + Pd(w / 2 * dx[j], h / 2 * dy[j]).rotate(-phi / 180 * acos(-1));
			points.push_back(vertex);
		}
	}

//	for (auto x: points)std::cout << x << '\n';
	std::vector<Pd> convexHull = ConvexHull(points);
	int m = convexHull.size();
//	for (auto x: convexHull)std::cout << x << '\n';
	double fm = 0;
	for (int i = 0; i < m; ++i) {
		fm -= cross(convexHull[i] - convexHull[(i + m - 1) % m], convexHull[i] - Pd(0, 0)) / 2;
	}
//	std::cerr << fz << ' ' << fm << '\n';
//	std::cerr << fz / fm << '\n';
	double ans = fz / fm * 100;
	std::cout << std::fixed << std::setprecision(1)<<ans<<" %\n";
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