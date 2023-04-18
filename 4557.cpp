//
// Created by mrx on 2023/3/17.
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

    bool operator <(const Point& rhs) const { return sgn(y - rhs.y) == 0 ? sgn(x - rhs.x) < 0 : sgn(y - rhs.y) < 0; }

    bool operator ==(const Point& rhs) const { return sgn(x - rhs.x) == 0 && sgn(y - rhs.y) == 0; }

    bool up() const { return sgn(y) == 0 ? sgn(x) >= 0 : sgn(y) > 0; }
};

using Pl = Point<i64>;
using Pd = Point<double>;

std::vector<Pl> ConvexHull(std::vector<Pl> points) {
    int n = points.size();
    std::sort(points.begin(), points.end());
    std::deque<Pl> dq;
    for (auto& point: points) {
        while (dq.size() > 1 && sgn(cross(dq[dq.size() - 1] - dq[dq.size() - 2], point - dq[dq.size() - 2])) <= 0)dq.pop_back();
        dq.push_back(point);
    }

    int k = int(dq.size());
    for (int i = n - 1; i >= 0; i--) {
        while (dq.size() > k && sgn(cross(dq[dq.size() - 1] - dq[dq.size() - 2], points[i] - dq[dq.size() - 2])) <= 0)dq.pop_back();
        dq.push_back(points[i]);
    }

    std::vector<Pl> ans(dq.begin(), dq.end());
    return ans;
}

std::vector<Pl> minkowski(std::vector<Pl> hullA, std::vector<Pl> hullB) {
    int n = hullA.size(), m = hullB.size();
    n--, m--;
    std::vector<Pl> sega(n), segb(m);
    for (int i = 1; i <= n; ++i) sega[i - 1] = hullA[i] - hullA[i - 1];
    for (int i = 1; i <= m; ++i) segb[i - 1] = hullB[i] - hullB[i - 1];
    std::vector<Pl> ans(n + m);
    ans[0] = hullA[0] + hullB[0];
    for (int i = 1, j = 0, k = 0; i < n + m; ++i) {
        ans[i] = ans[i - 1];
        if (j < n && (k == m || sgn(cross(sega[j], segb[k])) >= 0)) ans[i] += sega[j++];
        else ans[i] += segb[k++];
    }
    return ConvexHull(ans);
}


void solve() {
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<Pl> pointsA(n), pointsB(m);
    for (auto& point: pointsA) std::cin >> point;

    for (auto& point: pointsB) {
        std::cin >> point;
        point.x = -point.x, point.y = -point.y;
    }
    auto hullA = ConvexHull(pointsA);
//    std::cerr << "HA:\n";
//    for (auto x: hullA)std::cerr << x << '\n';
    auto hullB = ConvexHull(pointsB);
//    std::cerr << "HB:\n";
//    for (auto x: hullB)std::cerr << x << '\n';
    auto A_B = minkowski(hullA, hullB);
    std::vector<Pl> lines;
    for (int i = 0; i + 1 < A_B.size(); i++) {
        lines.emplace_back(A_B[i] - A_B[0]);
    }
//    std::cerr << "sum:\n";
//    for (auto x: A_B)std::cerr << x << '\n';

    auto in_hull = [](Pl p, std::vector<Pl>& lines) {
        if (cross(lines.back(), p) > 0 || cross(p, lines[0]) > 0) return false;
//        std::cout << p << "fuck\n";
        int pos = std::lower_bound(lines.begin(), lines.end(), p, [&](auto x, auto y) {
            return sgn(cross(x, y)) > 0 || (cross(x, y) == 0 && abs2(x) < abs2(y));
        }) - lines.begin();
        pos = (pos + lines.size() - 1) % lines.size();
//        std::cout << pos << ' ' << lines.size() << "!!!";
//        std::cout << lines[pos] << '\n';
        return cross(p - lines[pos], lines[(pos + 1) % lines.size()] - lines[pos]) <= 0;
    };

    while (q--) {
        Pl x;
        std::cin >> x;
        std::cout << in_hull(x - A_B[0], lines) << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    freopen("my.err", "w", stderr);
    solve();

    return 0;
}