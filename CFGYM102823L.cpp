#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <queue>
#include <array>
#include <map>
#include <set>
#include <iomanip>
#include <cassert>

using i64 = long long;

constexpr double eps = 1e-6;

template<typename T>
int sgn(T x) {
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

template<class T>
struct Line {
	Point<T> a, b;

	Line(Point<T> a, Point<T> b) : a(a), b(b) {}

	Line() {}

	Point<T> vec() const {
		return b - a;
	}
};

using P = Point<int>;
using L = Line<int>;

int toLeft(const P& p, const L& l) {
	return sgn(cross(p - l.a, l.vec()));
}

bool onLine(const P& p, const L& l) {
	return cross(p - l.a, l.vec()) == 0 && dot(p - l.a, p - l.b) <= 0;
}

Point<double> db(P x) {
	return Point<double>(x.x, x.y);
}

Point<double> intersection(const L& l1, const L& l2) {
	Line<double> p1, p2;
	p1.a = db(l1.a);
	p1.b = db(l1.b);
	p2.a = db(l2.a);
	p2.b = db(l2.b);
	return p1.a + p1.vec() * (cross(p2.a - p1.a, p2.vec()) / cross(p1.vec(), p2.vec()));
}

bool work(L w, L b) {
	L r1(w.a, b.a);
	L r2(w.b, b.b);

	if (cross(r1.vec(), r2.vec()) == 0) {
		std::cout << "inf\n";
		return true;
	}

	if (toLeft(r1.a, r2) * toLeft(r1.b, r2) < 0 && toLeft(r2.a, r1) * toLeft(r2.b, r1) < 0) {
		return false;
	}

	auto inter = intersection(r1, r2);

	if (std::abs(inter.x - w.a.x) <= std::abs(inter.x - b.a.x)) {
		std::cout << std::abs(cross(inter - db(w.a), inter - db(w.b))) / 2 << "\n";
	} else {
		std::cout << "inf\n";
	}
	return true;
}

void solve() {
	L w, b;
	std::cin >> w.a >> w.b >> b.a >> b.b;

	if (cross(w.vec(), b.vec()) == 0 && cross(w.vec(), b.a - w.a) == 0) {
		std::cout << "0\n";
		return;
	}

	if (toLeft(w.a, b) * toLeft(w.b, b) < 0 && toLeft(b.a, w) * toLeft(b.b, w) < 0) {
		std::cout << "0\n";
		return;
	}

	if (std::set{w.a, w.b, b.a, b.b}.size() == 3) {
		std::cout << "inf\n";
		return;
	}

	if (onLine(b.a, w) || onLine(b.b, w)) {
		std::cout << "inf\n";
		return;
	}

	if (onLine(w.a, b) || onLine(w.b, b)) {
		std::cout << "0\n";
		return;
	}

	if (toLeft(b.a, w) * toLeft(b.b, w) < 0) {
		std::cout << "0\n";
		return;
	}

	if (toLeft(w.a, b) * toLeft(w.b, b) < 0) {
		std::cout << "inf\n";
		return;
	}

	if (!work(w, b)) {
		std::swap(w.a, w.b);
		assert(work(w, b));
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t;
	std::cin >> t;

	std::cout << std::fixed << std::setprecision(12);
	for (int i = 1; i <= t; ++i) {
		std::cout << "Case " << i << ": ";
		solve();
	}

	return 0;
}