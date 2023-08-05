#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <numeric>
#include <queue>

using i64 = long long;
using db = double;
constexpr db eps = 1e-6;

int sgn(db x) {
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
	Point<db> operator *(const Y& rhs) const { return {x * rhs, y * rhs}; }

	template<class Y>
	Point<db> operator /(const Y& rhs) { return {x / rhs, y / rhs}; }

	friend db abs(const Point& lhs) { return std::sqrt(lhs.x * lhs.x + lhs.y * lhs.y); }

	friend i64 abs2(const Point& lhs) { return (lhs.x * lhs.x + lhs.y * lhs.y); }

	friend T cross(const Point& lhs, const Point& rhs) { return lhs.x * rhs.y - lhs.y * rhs.x; }

	friend T dot(const Point& lhs, const Point& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; }

	friend db angle(const Point& rhs) { return atan2(rhs.y, rhs.x); }

	Point rotate90() const { return {y, x}; }

	Point<db> rotate(db deg) { return {x * cos(deg) - y * sin(deg), x * sin(deg) + y * cos(deg)}; }

	bool operator <(const Point& rhs) const { return sgn(x - rhs.x) == 0 ? sgn(y - rhs.y) < 0 : sgn(x - rhs.x) < 0; }

	bool operator ==(const Point& rhs) const { return sgn(x - rhs.x) == 0 && sgn(y - rhs.y) == 0; }

	bool up() const { return sgn(y) == 0 ? sgn(x) >= 0 : sgn(y) > 0; }
};

using Pl = Point<i64>;
using Pd = Point<db>;


template<typename T>
struct Line {
	Point<T> a, v;

	Line(const Point<T>& a, const Point<T>& b) : a(a), v(b - a) {}

	template<class Y>
	Line(const Point<Y>& cp) : a(cp.a), v(cp.v) {}

	Pd point(db t) {
		return a + v * t;
	}

	friend Point<db> intersection(const Line<T> lhs, const Line<T> rhs) {
		db t = (db) cross(rhs.a - lhs.a, rhs.v) / cross(lhs.v, rhs.v);
		return lhs.v * t + Point<db>(lhs.a);
	}

	db dis(const Point<T>& rhs) {
		return std::abs(cross(rhs - a, v)) / v.abs();
	}

	Line rotate(db deg) {
		Line<db> ans(*this);
		ans.v = Rotate(v, deg);
		return ans;
	}
};

using Ll = Line<i64>;
using Ld = Line<db>;

bool isCross(Pd a, Pd b, Pd i, Pd j) {
	return sgn(cross(i - a, j - i)) * sgn(cross(i - b, j - i)) == -1 && sgn(cross(b - i, a - b)) * sgn(cross(b - j, a - b)) == -1;
}

bool onSeg(Pd a, Pd i, Pd j) {
	return sgn(cross(i - a, j - a)) == 0 && sgn(dot(a - i, a - j)) < 0;
}

Ll convert(std::pair<int, int> e) {
    auto [a, b] = e;
    Pl v = {1, a};
    Pl x = {0, b};
    return {x, x + v};
}

std::vector<Pl> convex_hull(std::vector<Pl> points) {
    std::deque<Pl> dq;
    int n = points.size();
    std::sort(points.begin(), points.end());

    for (auto& point: points) {
		while (dq.size() > 1 && sgn(cross(dq[dq.size() - 1] - dq[dq.size() - 2], point - dq[dq.size() - 2])) < 0)dq.pop_back();
		dq.push_back(point);
	}

	int k = int(dq.size());
	for (int i = n - 2; i >= 0; i--) {
		while (dq.size() > k && sgn(cross(dq[dq.size() - 1] - dq[dq.size() - 2], points[i] - dq[dq.size() - 2])) < 0)dq.pop_back();
		dq.push_back(points[i]);
	}

	std::vector<Pl> ans(dq.begin(), dq.end());
	return ans;
}

void solve() {
    int n;
    std::cin >> n;

    std::vector<Pl> points;
    for(int i = 0; i < n; ++i) {
        Pl p;
        char c;
        std::cin >> p >> c;
        if (c == 'Y') points.push_back(p);
    }

    // for(auto x: points) std::cout << x.x << ' ' << x.y << '\n';

    auto ans = convex_hull(points);


    std::cout << ans.size() - 1 << '\n';
    for (int i = 0; i < ans.size() - 1; ++i) std::cout << ans[i].x << ' ' << ans[i].y << '\n';

}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while(t--) solve();

    return 0;
}