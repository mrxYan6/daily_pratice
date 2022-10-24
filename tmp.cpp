#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <numeric>
#include <cmath>
#include <functional>
#include <queue>
#include <iomanip>
#include <cassert>

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

	friend int sgn(const point& a) {
		return a.y > 0 || (a.y == 0 && a.x > 0) ? 1 : -1;
	}

	friend point rotate(const point& a) {
		return {-a.y, a.x};
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

bool onLeft(Pd a, Ld l) {
	return sgn(cross(l.dir, a - l.a)) > 0;
}

using Polygen = std::vector<Pd>;

Polygen hp(std::vector<Ld> lines) {
	std::sort(lines.begin(), lines.end(), [&](auto l1, auto l2) {
		auto d1 = l1.dir;
		auto d2 = l2.dir;
		if (sgn(d1) != sgn(d2)) {
			return sgn(d1) == 1;
		}

		return sgn(cross(d1, d2)) > 0;
	});

	std::deque<Ld> ls;
	std::deque<Pd> ps;
	for (auto l: lines) {
		if (ls.empty()) {
			ls.push_back(l);
			continue;
		}

		while (!ps.empty() && !onLeft(ps.back(), l)) {
			ps.pop_back();
			ls.pop_back();
		}

		while (!ps.empty() && !onLeft(ps.front(), l)) {
			ps.pop_front();
			ls.pop_front();
		}

		if (sgn(cross(l.dir, ls.back().dir)) == 0) {
			if (sgn(dot(l.dir, ls.back().dir)) > 0) {
				if (!onLeft(ls.back().a, l)) {
					assert(ls.size() == 1);
					ls[0] = l;
				}
				continue;
			}
			return {};
		}

		ps.push_back(intersection(ls.back(), l));
		ls.push_back(l);
	}

	while (!ls.empty() && !onLeft(ps.back(), ls[0])) {
		ps.pop_back();
		ls.pop_back();
	}

	if (ls.size() <= 2)return {};
	ps.push_back(intersection(ls[0], ls.back()));
	return {ps.begin(), ps.end()};
}

void solve() {
	int n, h;
	std::cin >> n >> h;

	double w;
	std::cin >> w;

	std::vector<Ld> lines;
	std::vector<Pd> p(n);
	for (int i = 0; i < n; i++) {
		int x, y;
		std::cin >> x >> y;
		p[i] = Pd(x, y);
	}
	for (int i = 0; i < n; i++) {
		auto u = rotate(p[(i + 1) % n] - p[i]);
		u = u / std::sqrt(dot(u, u)) * w;
		lines.emplace_back(p[i] + u, p[(i + 1) % n] + u);
	}

	int X, Y, Z;
	std::cin >> X >> Y >> Z;

	Pd s(X, Y);

	p = hp(lines);
	if (p.empty()) {
		std::cout << 0.0 << "\n";
		return;
	}

	n = p.size();

	bool inside = true;
	for (int i = 0; i < n; i++) {
		if (cross(p[(i + 1) % n] - p[i], s - p[i]) < 0) {
			inside = false;
		}
	}

	if (!inside && Z <= h) {
		std::cout << 0.0 << "\n";
		return;
	}

	lines.clear();

	double T = 1.0 * Z / (Z - h);
	for (int i = 0; i < n; i++) {
		if (cross(p[(i + 1) % n] - p[i], s - p[i]) > 0) {
			lines.emplace_back(p[i], p[(i + 1) % n]);
		} else {
			auto u = s + (p[i] - s) * T;
			auto v = s + (p[(i + 1) % n] - s) * T;
			lines.emplace_back(u, v);
		}
	}

	p = hp(lines);
	n = p.size();

	double ans = 0;
	for (int i = 0; i < n; i++) {
		ans += cross(p[i], p[(i + 1) % n]);
	}
	ans /= 2;
	std::cout << ans << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cout << std::fixed << std::setprecision(10);

	int t;
	std::cin >> t;

	while (t--) {
		solve();
	}

	return 0;
}