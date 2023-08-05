#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <numeric>

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

void solve() {
    int n;
    std::cin >> n;

    std::vector<std::pair<int,int>> lines(n);

    std::vector<int> idx(n);
    std::iota(idx.begin(), idx.end(), 0);

    for (auto& [a, b] : lines) {
        std::cin >> a >> b;
    }

    std::sort(idx.begin(), idx.end(), [&] (auto i, auto j) {
        auto x = lines[i], y = lines[j];
        return x.first == y.first ? x.second > y.second : x.first < y.first;
    });

    idx.erase(std::unique(idx.begin(), idx.end(), [&] (auto i, auto j) {
        auto x = lines[i], y = lines[j];
        return x.first == y.first;
    }), idx.end());

    // for (int i = 0; i < idx.size(); ++i) {
    //     std::cout << lines[idx[i]].first << ' ' << lines[idx[i]].second << '\n';
    // }

    std::vector<int> ans;

    for (int i = 0; i < idx.size(); ++i) {
        while(ans.size() >= 2) {
            auto l = convert(lines[ans[ans.size() - 2]]), m = convert(lines[ans[ans.size() - 1]]), r = convert(lines[idx[i]]);
            auto left_inter = intersection(l, m), right_inter = intersection(m, r);
            if (sgn(right_inter.x - left_inter.x) <= 0) ans.pop_back();
            else break;
        }
        ans.push_back(idx[i]);
    }

    std::sort(ans.begin(), ans.end());

    for (auto x : ans) std::cout << x + 1 << ' ';
    std::cout << '\n';

}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    solve();

    return 0;
}