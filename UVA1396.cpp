//
// Created by mrx on 2022/11/8.
//
#include <iomanip>
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

	bool polarAngleCmp(const Point& rhs) const {
		return up() ^ rhs.up() ? up() > rhs.up() : cross(*this, rhs) < 0;
	}
};

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

	friend Point<double> intersection(const Line<T> lhs, const Line<T> rhs) {
		double t = (double) cross(rhs.a - lhs.a, rhs.v) / cross(lhs.v, rhs.v);
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

	bool operator <(const Line& rhs) const {
		return v.polarAngleCmp(rhs.v);
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

bool onLeft(Ld line, Pd p) {
	return sgn(cross(line.v, p - line.a)) > 0;
}

std::vector<Pd> halfPlaneIntersection(std::vector<Ld> lines) {
	sort(lines.begin(), lines.end());

	int n = lines.size();
	std::deque<Pd> ps;
	std::deque<Ld> ls;
	for (auto l: lines) {
		if (ls.empty()) {
			ls.push_back(l);
			continue;
		}

		while (!ps.empty() && !onLeft(l, ps.back()))ps.pop_back(), ls.pop_back();
		while (!ps.empty() && !onLeft(l, ps.front()))ps.pop_front(), ls.pop_front();

		if (sgn(cross(l.v, ls.back().v)) == 0) {
			//特判平行
			if (sgn(dot(l.v, ls.back().v)) < 0) {
				return {};
			}
		}

		ps.push_back(intersection(ls.back(), l));
		ls.push_back(l);
	}

	while (!ps.empty() && !onLeft(ls.front(), ps.back()))ls.pop_back(), ps.pop_back();
	if (ls.size() <= 2)return {};
	ps.push_back(intersection(ls.front(), ls.back()));

	return {ps.begin(), ps.end()};
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;
	while (std::cin >> n && n) {
		std::vector<Pd> island(n);
		for (int i = 0; i < n; ++i)std::cin >> island[i];
		double l = 0, r = 1e9;
		double ans = 0;

		std::function<bool(double)> check = [&](double x) -> bool {
			std::vector<Ld> lines;

			for (int i = 0; i < n; ++i) {
				Ld lin(island[i], island[(i + 1) % n]);
				Pd vec = lin.v.rotate90();
				lin.a += (vec) / abs(vec) * x;
			}
			auto ans = halfPlaneIntersection(lines);
			return !ans.empty();
		};

		for (int i = 0; i < 64; ++i) {
			double m = (l + r) / 2;
			if (check(m)) {
				l = m;
				ans = m;
			} else {
				r = m;
			}
		}
		std::cout << std::fixed << std::setprecision(5) << ans << '\n';
	}
	return 0;
}