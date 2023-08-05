#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <iomanip>

using i64 = long long;
using i128 = __int128;

struct Point {
    i64 x, y;

    Point(i64 x, i64 y) : x(x), y(y) {}

    friend i128 cross(const Point &a, const Point &b) {
        return (i128) a.x * b.y - (i128) a.y * b.x;
        // return a.x * b.y - a.y * b.x;
    }

    Point operator - (const Point & rhs) {
        return Point(x - rhs.x, y - rhs.y);
    }

    friend std::ostream & operator << (std::ostream &os, const Point &p) {
        os << "(" << p.x << ' ' << p.y << ")";
        return os;
    }
};

void solve() {
    int n;
    i64 d;
    std::cin >> n >> d;

    std::vector<i64> a(n), x(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i] >> x[i];
    }

    std::vector<i64> sum(n + 1);
    for (int i = 0; i < n; ++i) {
        sum[i + 1] = sum[i] + a[i];
    }

    std::vector<Point> hull;

    auto add = [&](i64 x, i64 y) {
        Point p(x, y);
        while (hull.size() >= 2 && cross(hull.back() - hull[hull.size() - 2], p - hull.back()) >= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    };
    auto query = [&] (i64 x, i64 y) {
        Point p(x, y);

        int l = 1, r = hull.size() - 1, ans = 0;
        while(l <= r) {
            int m = (l + r) >> 1;
            // std::cout << p - hull[m - 1] << ' ' << p - hull[m] << ' ' << cross(p - hull[m - 1], p - hull[m]) << '\n';
            if (cross(hull[m - 1] - p, hull[m] - p) <= 0) {
                ans = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        return hull[ans];
    };

    double ans = 0;

    for (int i = 0; i <= n; ++i) {
        if (i) {
            auto back = query(sum[i], x[i - 1] + i * d);
            // std::cout << back.x <<  ' ' << back.y << '\n';
            // std::cout << sum[i] << ' ' << i * d + x[i - 1] << '\n';
            ans += 1.0 * (sum[i] - back.x) / (x[i - 1] + i * d - back.y);
            // std::cout << ans << '\n';
        }
        add(sum[i], (i + 1) * d);
    }
    std::cout << std::fixed << std::setprecision(0) << ans << '\n';
}


int main () {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();
    
    return 0;
}