#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <iomanip>
#include <cmath>

using i64 = long long;
using i128 = __int128;

struct Point {
    i64 x, y;

    Point(i64 x, i64 y) : x(x), y(y) {}

    Point() {}

    friend i64 cross(const Point &a, const Point &b) {
        return a.x * b.y - a.y * b.x;
    }

    Point operator - (const Point & rhs) {
        return Point(x - rhs.x, y - rhs.y);
    }

    friend double abs(const Point &p) {
        return std::sqrt(p.x * p.x + p.y * p.y);
    }

    friend std::ostream & operator << (std::ostream &os, const Point &p) {
        os << "(" << p.x << ' ' << p.y << ")";
        return os;
    }

    friend bool operator < (const Point &a, const Point &b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    }
};

std::vector<Point> ConvexHull(std::vector<Point> points) {
	int n = points.size();
	std::sort(points.begin(), points.end());
	std::deque<Point> dq;

	for (auto point: points) {
		while (dq.size() > 1 && (cross(dq[dq.size() - 1] - dq[dq.size() - 2] , point - dq[dq.size() - 2])) <= 0)dq.pop_back();
		dq.push_back(point);
	}

	int k = int(dq.size());
	for (int i = n - 1; i >= 0; i--) {
		while (dq.size() > k && (cross(dq[dq.size() - 1] - dq[dq.size() - 2] , points[i] - dq[dq.size() - 2])) <= 0)dq.pop_back();
		dq.push_back(points[i]);
	}

	std::vector<Point> ans(dq.begin(), dq.end());
	return ans;
}


void solve() {
    int n, l;
    std::cin >> n >> l;

    std::vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> x[i] >> y[i];
    }

    std::vector<Point> points(n);
    for(int i = 0; i < n; ++i) {
        points[i] = Point(x[i], y[i]);
    }

    auto hull = ConvexHull(points);

    double ans = 2 * l * acos(-1);

    for (int i = 1; i < hull.size(); ++i) {
        ans += abs(hull[i] - hull[i - 1]);
    }

    std::cout << std::fixed << std::setprecision(0) << ans << '\n';

}


int main () {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while(t--) {
        solve();
        if(t) std::cout << "\n";
    }
    return 0;
}