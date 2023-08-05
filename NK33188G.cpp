#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <cmath>
#include <iomanip>

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
	Point operator *(const Y& rhs) const { return {x * rhs, y * rhs}; }

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

template<typename T>
struct Line {
	Point<T> a, v;

	Line(const Point<T>& a, const Point<T>& b) : a(a), v(b - a) {}

	template<class Y>
	Line(const Point<Y>& cp) : a(cp.a), v(cp.v) {}

	Pl point(db t) {
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

using Ld = Line<db>;
using Ll = Line<i64>;

bool isCross(Pl a, Pl b, Pl i, Pl j) {
	return sgn(cross(i - a, j - i)) * sgn(cross(i - b, j - i)) == -1 && sgn(cross(b - i, a - b)) * sgn(cross(b - j, a - b)) == -1;
}

bool onSeg(Pl a, Pl i, Pl j) {
	return sgn(cross(i - a, j - a)) == 0 && sgn(dot(a - i, a - j)) <= 0;
}


template<typename Point>
std::vector<Point> ConvexHull(std::vector<Point> points) {
    int n = points.size();
    std::sort(points.begin(), points.end());
    std::deque<Point> dq;

    for (auto& point: points) {
        while (dq.size() > 1 && sgn(cross(dq[dq.size() - 1] - dq[dq.size() - 2], point - dq[dq.size() - 2])) <= 0)dq.pop_back();
        dq.push_back(point);
    }

    int k = int(dq.size());
    for (int i = n - 1; i >= 0; i--) {
        while (dq.size() > k && sgn(cross(dq[dq.size() - 1] - dq[dq.size() - 2], points[i] - dq[dq.size() - 2])) <= 0)dq.pop_back();
        dq.push_back(points[i]);
    }

    std::vector<Point> ans(dq.begin(), dq.end());
    return ans;
}

template <typename Point>
std::vector<Point> minkowski(std::vector<Point> hullA, std::vector<Point> hullB) {
    int n = hullA.size(), m = hullB.size();
    n--, m--;
    std::vector<Point> sega(n), segb(m);
    for (int i = 1; i <= n; ++i) sega[i - 1] = hullA[i] - hullA[i - 1];
    for (int i = 1; i <= m; ++i) segb[i - 1] = hullB[i] - hullB[i - 1];
    std::vector<Point> ans(n + m);
    ans[0] = hullA[0] + hullB[0];
    for (int i = 1, j = 0, k = 0; i < n + m; ++i) {
        ans[i] = ans[i - 1];
        if (j < n  && (k == m || sgn(cross(sega[j], segb[k])) >= 0)) ans[i] += sega[j++];
        else ans[i] += segb[k++];
    }
    return ConvexHull(ans);
}



bool point_in_polygon(Pl p, std::vector<Pl> a) {
	int n = a.size();
	int s = 0;
	for (int i = 1; i < n; i++) {
		auto u = a[i - 1], v = a[i];
		if (onSeg(p, u, v))return true;
		if (sgn(u.y - v.y) <= 0)std::swap(u, v);
		if (sgn(p.y - u.y) > 0 || sgn(p.y - v.y) <= 0)continue;
		if (sgn(cross(v - p, u - p)) == 1)++s;
	}
	return s & 1;
}

void solve() {
    int n;
    std::cin >> n;
    std::vector<Pl> a(n);
    
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        a[i].x *= -1;
        a[i].y *= -1;
    }

    int m;
    std::cin >> m;
    std::vector<Pl> b(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }

    auto hulla = ConvexHull(a);
    auto hullb = ConvexHull(b);

    auto sum = ConvexHull(minkowski(a, b));


    Pl va, vb;
    std::cin >> va >> vb;
    Pl vec = va - vb;
    // for (auto x : sum) std::cout << x << '\n';
    // std::cout << '\n';
    Pl o(0, 0);
    if (point_in_polygon(o, sum)) {
        std::cout << 0 << '\n';
    } else if (vec == Pl(0,0)) {
        std::cout << -1 << '\n';
    } else {
        int s = sum.size();
        double ans = 1e20;

        auto check = [&] (Pl a, Pl u, Pl v) {
            // std::cout << a << ' ' << u << ' ' << v << ":: " << '\n';
            // std::cout << cross(a, u) << ' ' << cross(a, v) << ' ' << dot(a, u) << ' ' << dot(a, v) << '\n';
            if (cross(a, u) == 0 && dot(a, u) >= 0) return 1;
            if (cross(a, v) == 0 && dot(a, v) >= 0) return 1;
            if (sgn(cross(a, u)) * sgn(cross(a, v)) == -1 && sgn(dot(a, u)) > 1)  return 1;
            return 0;
        };
        for (int i = 1; i < s; ++i) {
            auto u = sum[i - 1], v = sum[i];
            if (check(vec, u, v)) {
                auto t = intersection(Ld{o, vec}, Ld{u, v});
                ans = std::min(ans, abs(t) /  abs(vec));
            }
        }
        if (ans > 1e18) std::cout << -1 << '\n';
        else std::cout << ans << '\n';
    }
}

int main () {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    solve();

    return 0;
}