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

	friend double angle(const Point& rhs) { return atan2(rhs.y, rhs.x); }

	Point rotate90() const { return {y, x}; }

	Point<double> rotate(double deg) { return {x * cos(deg) - y * sin(deg), x * sin(deg) + y * cos(deg)}; }

	bool operator <(const Point& rhs) const { return sgn(x - rhs.x) == 0 ? sgn(y - rhs.y) < 0 : sgn(x - rhs.x) < 0; }

	bool operator ==(const Point& rhs) const { return sgn(x - rhs.x) == 0 && sgn(y - rhs.y) == 0; }

	bool up() const { return sgn(y) == 0 ? sgn(x) >= 0 : sgn(y) > 0; }
};

using Pl = Point<i64>;
using Pd = Point<double>;

void solve() {
    Pl p,a,b;
    i64 v,t;
    std::cin >> p >> a >> b >> v >> t;
    v *= 2;
    p.x *= 2, a.x *= 2, b.x *= 2;
    p.y *= 2, a.y *= 2, b.y *= 2;

    i64 r = v * t;

    Pl mid = a + b;
    mid.x /= 2;
    mid.y /= 2;
    // std::cout << "mid: " << mid << '\n';
    // std::cout << "r: " << r << '\n';
    double ans = 0;
    if (r * r >= abs2(mid - p)) {
        // 中点在原内
        if (r * r > abs2(b - p)) {
            //B 在原内
            // std::cout << "case1 \n";
            ans = std::acos(-1) * r * r;
        } else {
            // std::cout << "case2 \n";
            double theta = acos(r / abs(b - p));
            ans = (acos(-1) - theta * 2) * r * r + 2 * r * sqrt(abs2(b - p) - r * r);
        }
    } else {
        // 中点在原外
        // std::cout << "case3 \n";

        double theta = acos(abs(mid - p) / abs(b - p)) + acos(r / abs(b - p));
        ans = abs(mid - p) * abs(b - mid) + r * sqrt(abs2(b - p) - r * r) + (acos(-1) - theta) * r * r;
    }
    std::cout << std::fixed << std::setprecision(12) << ans / 4 << '\n';
}

int main () {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}