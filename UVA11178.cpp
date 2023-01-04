#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <numeric>
#include <cmath>
#include <functional>
#include <iomanip>

using ll = long long;

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

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int t;
	std::cin >> t;
	while (t--) {
		std::vector<Pl> triangle(3);
		for (int i = 0; i < 3; ++i)std::cin >> triangle[i];
		std::vector<Pd> inner(3);
		auto getP = [&](Pl A, Pl B, Pl C) {
			double a1 = acos(dot(A - B, C - B) / abs(A - B) / abs(C - B));
			Ld la(B, C);
			la = la.rotate(a1 / 3);

			double a2 = acos(dot(A - C, B - C) / abs(A - C) / abs(B - C));
			Ld lb(C, A);
			lb = lb.rotate(2 * a2 / 3);
			return intersection(la, lb);
		};
		inner[0] = getP(triangle[0], triangle[1], triangle[2]);
		inner[1] = getP(triangle[1], triangle[2], triangle[0]);
		inner[2] = getP(triangle[2], triangle[0], triangle[1]);
		for (int i = 0; i < 3; ++i)std::cout << std::fixed << std::setprecision(6) << inner[i] << ' ';
		std::cout << '\n';
	}

	return 0;
}