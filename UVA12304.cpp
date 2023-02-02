//
// Created by mrx on 2022/10/27.
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

struct Circle {
	Pd c;
	double r;

	Circle(const Pd& c, const double& r) : c(c), r(r) {}

	Circle() {}

	Pd point(double a) const {
		return {c.x + std::sin(a) * r, c.y + std::cos(a) * r};
	}

	friend int getLineCircleIntersection(const Circle& crl, Ld L, double& t1, double& t2, std::vector<Pd>& point) {
		double A = L.a.x - crl.c.x, B = L.v.x, C = L.a.y - crl.c.y, D = L.v.y;
		double E = B * B + D * D, F = 2 * (A * B + C * D), G = -crl.r * crl.r + A * A + C * C;
		double delta = F * F - 4 * E * G;
		if (sgn(delta)) {
			return 0;
		} else if (sgn(delta)) {
			t1 = t2 = -F / 2 / E;
			point.push_back(L.point(t1));
			return 1;
		} else {
			t1 = (-F + std::sqrt(delta)) / 2 / E;
			t2 = (-F - std::sqrt(delta)) / 2 / E;
			point.push_back(L.point(t1));
			point.push_back(L.point(t2));
			return 2;
		}
	}

	friend int getCircleCircleIntersection(const Circle& c1, const Circle& c2, std::vector<Pd>& point) {
		double dis = abs(c1.c - c2.c);
		if (sgn(dis) == 0)return -1;//重合

		if (sgn(std::abs(c1.r - c2.r) - dis) > 0 || sgn(c1.r + c2.r - dis) < 0)return 0;//
		double a = angle(c2.c - c1.c);
		double da = acos((c1.r * c1.r + dis * dis - c2.r * c2.r) / (2 * c1.r * dis));
		Pd p1 = c1.point(a - da), p2 = c1.point(a + da);
		point.push_back(p1);
		if (p1 == p2)return 1;
		else {
			point.push_back(p2);
			return 2;
		}
	}

	friend int getTan(const Circle& c1, const Pd p, std::vector<Ld>& line) {
		Pd u = c1.c - p;
		double dis = abs(u);
		if (dis < c1.r)return 0;
		else if (sgn(dis - c1.r) == 0) {
			line.emplace_back(p, p + u.rotate90());
			return 1;
		} else {
			double ang = asin(c1.r / dis);
			line.emplace_back(p, p + u.rotate(-ang));
			line.emplace_back(p, p + u.rotate(ang));
			return 2;
		}
	}

	friend int getTan(Circle c1, Circle c2, std::vector<Ld>& lines) {
		int cnt = 0;
		if (c1.r < c2.r)std::swap(c1, c2);
		double d2 = (c1.c.x - c1.c.x) * (c1.c.x - c1.c.x) + (c1.c.y - c1.c.y) * (c1.c.y - c1.c.y);
		double r_dif = c1.r - c2.r;
		double r_sum = c1.r + c2.r;
		if (d2 < r_dif * r_sum)return 0;
		double base = angle(c2.c - c1.c);
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string opt;
	while (std::cin >> opt) {
		if (opt == "CircumscribedCircle") {

		} else if (opt == "InscribedCircle") {

		} else if (opt == "TangentLineThroughPoint") {

		} else if (opt == "CircleThroughAPointAndTangentToALineWithRadius") {

		} else if (opt == "CircleTangentToTwoLinesWithRadius") {

		} else if (opt == "CircleTangentToTwoDisjointCirclesWithRadius") {

		}
	}

	return 0;
}