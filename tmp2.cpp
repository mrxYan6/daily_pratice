#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <queue>
#include <array>
#include <map>
#include <cassert>
#include <iomanip>
#include <random>

using db = double;
constexpr db eps = 1e-6;
const db pi = acos(-1);
using i64 = long long;

int sgn(db x) {
	return x < -eps ? -1 : x > eps;
}

int sgn(i64 x) {
	return x < 0 ? -1 : x > 0;
}

int cmp(db x, db y) { return sgn(x - y); }


//a11*x + a12*y = b1,  a21*x + a22*y = b2, 返回pair(x,y)
std::pair<db, db> solve(db a11, db a12, db b1, db a21, db a22, db b2) {
	db z = (a11 * a22 - a12 * a21);
	db x = (b1 * a22 - a12 * b2) / z;
	db y = (b2 * a11 - b1 * a21) / z;
	return {x, y};
}

//解方程 ax^2+bx+c=0, 解为x1,x2(x1<=x2)
bool solve_eqution(db a, db b, db c, db& x1, db& x2) {
	db delta = b * b - 4 * a * c;
	if (sgn(delta) == -1)return 0;
	db q, t = sqrt(delta);
	if (sgn(b) == -1)q = -0.5 * (b - t);
	else q = -0.5 * (b + t);
	x1 = q / a;
	x2 = c / q;
	if (cmp(x1, x2) == 1)std::swap(x1, x2);
	return 1;
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

	friend T abs2(const Point& lhs) { return (lhs.x * lhs.x + lhs.y * lhs.y); }

	friend T cross(const Point& lhs, const Point& rhs) { return lhs.x * rhs.y - lhs.y * rhs.x; }

	friend T dot(const Point& lhs, const Point& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; }

	friend db angle(const Point& rhs) { return atan2(rhs.x, rhs.y); }

	//逆时针
	Point rotate90() const { return {-y, x}; }

	Point<db> strech(db l) { return *this * l / abs(*this); }

	//逆时针
	Point<db> rotate(db deg) { return {x * cos(deg) - y * sin(deg), x * sin(deg) + y * cos(deg)}; }

	bool operator <(const Point& rhs) const { return sgn(x - rhs.x) == 0 ? sgn(y - rhs.y) < 0 : sgn(x - rhs.x) < 0; }

	bool operator ==(const Point& rhs) const { return sgn(x - rhs.x) == 0 && sgn(y - rhs.y) == 0; }

	friend db get_angle(const Point& lhs, const Point& rhs) { return atan2(std::abs(cross(lhs, rhs)), dot(lhs, rhs)); }

	bool up() const { return sgn(y) == 0 ? sgn(x) >= 0 : sgn(y) > 0; }
};

using Pl = Point<i64>;
using Pd = Point<db>;

template<typename T>
struct Line {
	Point<T> a, v;

	Line(const Point<T>& a, const Point<T>& b) : a(a), v(b - a) {}

	template<class Y>
	explicit Line(const Line<Y>& cp) : a(cp.a), v(cp.v) {}

	Pd point(db t) { return a + v * t; }

	friend Point<db> intersection(const Line<T> lhs, const Line<T> rhs) {
		db t = (db) cross(rhs.a - lhs.a, rhs.v) / cross(lhs.v, rhs.v);
		return lhs.v * t + Point<db>(lhs.a);
	}

	db dis(const Point<T>& rhs) { return std::abs(cross(rhs - a, v)) / v.abs(); }

	Line rotate(db deg) {
		Line<db> ans(*this);
		ans.v = Rotate(v, deg);
		return ans;
	}
};

using Ll = Line<i64>;
using Ld = Line<db>;

//线段ab,ij是否香蕉
bool isCross(Pd a, Pd b, Pd i, Pd j) {
	return sgn(cross(i - a, j - i)) * sgn(cross(i - b, j - i)) == -1
	       && sgn(cross(b - i, a - b)) * sgn(cross(b - j, a - b)) == -1;
}

//a是否在线段ij上
bool onSeg(Pd a, Pd i, Pd j) {
	return sgn(cross(i - a, j - a)) == 0 && sgn(dot(a - i, a - j)) < 0;
}

//半瓶平面角用
bool onLeft(const Pd& a, const Ld& l) {
	return cross(l.v, a - l.a) > 0;
}

using polygen = std::vector<Pd>;

db Polygen_Square(polygen& x) {
	db s = 0;
	for (int i = 1; i < x.size(); ++i) {
		s += cross(x[i - 1], x[i]);
	}
	return std::abs(s) / 2;//s>0:点是逆时针顺序,s<0:点是顺时针顺序
}

//求多边形重心
Pd polycenter(polygen a) {
	int n = a.size();
	Pd ans(0, 0);
	a[0] = a[n];
	for (int i = 0; i < n; i++)ans = ans + (a[i] + a[i + 1]) * cross(a[i], a[i + 1]);
	return ans / Polygen_Square(a) / 6;
}

//判点在是否在多边形内或边上
bool point_in_polygon(Pd p, const polygen& a) {
	int n = a.size();
	int s = 0;
	for (int i = 0; i < n; i++) {
		Pd u = a[i], v = a[(i + 1) % n];
		if (onSeg(p, u, v))return true;
		if (cmp(u.y, v.y) <= 0)std::swap(u, v);
		if (cmp(p.y, u.y) > 0 || cmp(p.y, v.y) <= 0)continue;
		if (sgn(cross(v - p, u - p)) == 1)++s;
	}
	return s & 1;
}

std::vector<Pd> ConvexHull(std::vector<Pd> points) {
	int n = points.size();
	std::sort(points.begin(), points.end());
	std::deque<Pd> dq;

	for (auto& point: points) {
		while (dq.size() > 1 && sgn(cross(dq[dq.size() - 1] - dq[dq.size() - 2], point - dq[dq.size() - 2])) <= 0)dq.pop_back();
		dq.push_back(point);
	}

	int k = int(dq.size());
	for (int i = n - 1; i >= 0; i--) {
		while (dq.size() > k && sgn(cross(dq[dq.size() - 1] - dq[dq.size() - 2], points[i] - dq[dq.size() - 2])) <= 0)dq.pop_back();
		dq.push_back(points[i]);
	}

	std::vector<Pd> ans(dq.begin(), dq.end());
	return ans;
}


//旋转卡壳,求凸包直径
i64 rotateCalipers(std::vector<Pl>& hull) {
	i64 d = 0;
	int n = hull.size();
	n--;
	if (n == 2)return abs2(hull[0] - hull[1]);
	int j = 2;
	for (int i = 0; i < n; ++i) {
		while (cross(hull[i + 1] - hull[i], hull[j] - hull[i]) < cross(hull[i + 1] - hull[i], hull[j + 1] - hull[i]))j = j < n - 1 ? j + 1 : 0;
		d = std::max({d, abs2(hull[i] - hull[j]), abs2(hull[i + 1] - hull[j])});
	}
	return d;
}

//输入lines是半平面,返回hp
//通常需要考虑添加边界
polygen hp(std::vector<Ld>& lines) {
	std::sort(lines.begin(), lines.end(), [&](auto l1, auto l2) {
		return l1.v.up() ^ l2.v.up() ? l1.v.up() == 1 : sgn(cross(l1.v, l2.v)) > 0;
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

		while (!ps.empty() && !onLeft(ps[0], l)) {
			ps.pop_front();
			ls.pop_front();
		}

		if (cross(l.v, ls.back().v) == 0) {
			if (dot(l.v, ls.back().v) > 0) {
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

	while (!ps.empty() && !onLeft(ps.back(), ls[0])) {
		ps.pop_back();
		ls.pop_back();
	}
	if (ls.size() <= 2) {
		return {};
	}
	ps.push_back(intersection(ls[0], ls.back()));

	return {ps.begin(), ps.end()};
}

//simpson
db f(db x) { return x; }

db simpson(double l, double r) {
	return (f(l) + f(r) + 4 * f((l + r) / 2)) * (r - l) / 6.0;
}

// 定积分[l,r]f(x)dx
db rsimpson(db l, db r) {
	db mid = (l + r) / 2;
	if (sgn(simpson(l, r) - simpson(l, mid) - simpson(mid, r)) == 0) return simpson(l, mid) + simpson(mid, r);
	return rsimpson(l, mid) + rsimpson(mid, r);
}

Pd Norm(const Pd& a) {
	auto tmp = a * (1 / abs(a));
	tmp = tmp * 10000;
	return tmp;
}

bool parallel(const Ld& a, const Ld& b) {
	return !sgn(cross(a.v, b.v));
}

int seg_int_seg(Pd a, Pd b, Pd p, Pd q) {
	int d1 = sgn(cross(b - a, p - a)), d2 = sgn(cross(b - a, q - a));
	int d3 = sgn(cross(q - p, a - p)), d4 = sgn(cross(q - p, b - p));
	if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2)return 1; //有交点,且交点不在端点
	if ((d1 == 0 && onSeg(p, a, b)) ||
	    (d2 == 0 && onSeg(q, a, b)) ||
	    (d3 == 0 && onSeg(a, p, q)) ||
	    (d4 == 0 && onSeg(b, p, q)))
		return -1; //重合或交点在端点上
	return 0;
}


struct circle {
	Pd c;
	db r;

	circle(Pd p = Pd(0, 0), db x = 1) : c(p), r(x) {}

	Pd point(db a) { return Pd(c.x + r * cos(a), c.y + r * sin(a)); }
};

//直线上截取某一点连线,在圆的函数中使用
Pd lerp(Pd a, Pd b, db t) { return a * (1 - t) + b * t; }

//过点p做圆的切线
int circletan(Pd p, circle C, Pd v[]) {
	Pd u = C.c - p;
	db d = abs(u);
	if (sgn(d - C.r) == -1)return 0;
	if (sgn(d - C.r) == 0) {
		v[0] = u.rotate90();
		return 1;
	}
	db a = asin(C.r / d);
	v[0] = u.rotate(-a);
	v[1] = u.rotate(a);
	return 2;
}

//两圆共切线,返回切线条数,无数条返回-1, v1[i],v2[i]第i条切线在圆A,B上的切点
int circle_tan(circle A, circle B, Pd v1[], Pd v2[]) {
	int cnt = 0;
	if (cmp(A.r, B.r) == -1)std::swap(A, B), std::swap(v1, v2);
	db d2 = abs2(A.c - B.c);
	db rsub = A.r - B.r;
	db rsum = A.r + B.r;
	if (sgn(d2 - rsub * rsub) == -1)return 0;//内含
	db a = atan2(B.c.y - A.c.y, B.c.x - A.c.x);
	if (!sgn(d2) && !sgn(A.r - B.r))return -1;//重合,无数切线
	if (!sgn(d2 - rsub * rsub)) {//内切,找到切点
		v1[cnt] = A.point(a);
		v2[cnt] = B.point(a);
		++cnt;
		return 1;
	}
	db b = acos((A.r - B.r) / sqrt(d2));
	v1[cnt] = A.point(a + b);
	v2[cnt++] = B.point(a + b);
	v1[cnt] = A.point(a - b);
	v2[cnt++] = B.point(a - b);
	if (!sgn(d2 - rsum * rsum)) {
		v1[cnt] = A.point(a);
		v2[cnt++] = B.point(pi + a);
	} else if (sgn(d2 - rsum * rsum) == 1) {
		b = acos((A.r + B.r) / sqrt(d2));
		v1[cnt] = A.point(a + b);
		v2[cnt++] = B.point(pi + a + b);
		v1[cnt] = A.point(a - b);
		v2[cnt++] = B.point(pi + a - b);
	}
	return cnt;
}

//圆与直线交点,lerp(a,b,x1),lerp(a,b,x2)
bool circle_int_line(circle c, Pd a, Pd b, db& x1, db& x2) {
	Pd d = b - a;
	db A = dot(d, d), B = dot(d, (a - c.c)) * 2.0, C = dot(a - c.c, a - c.c) - c.r * c.r;
	return solve_eqution(A, B, C, x1, x2);
}

//圆圆相交的交点
bool circle_int_circle(circle a, circle b, Pd& p1, Pd& p2) {
	db d = abs(a.c - b.c);
	if (cmp(d, a.r + b.r) == 1 || cmp(d, abs(a.r - b.r)) == -1)return true;
	db l = (abs2(a.c - b.c) + a.r * a.r - b.r * b.r) / (2 * d);
	db h = sqrt(a.r * a.r - l * l);
	Pd vl = (b.c - a.c).strech(l), vh = vl.rotate90().strech(h);
	p1 = a.c + vl + vh;
	p2 = a.c + vl - vh;
	return false;
}

//圆和三角形abo交的面积，o是圆心
db circle_int_triangle(circle c, Pd a, Pd b) {
	if (sgn(cross(a - c.c, b - c.c)) == 0)return 0;
	Pd q[5];
	int cnt = 0;
	db t0, t1;
	q[cnt++] = a;
	if (circle_int_line(c, a, b, t0, t1)) {
		if (0 <= t0 && t0 <= 1)q[cnt++] = lerp(a, b, t0);
		if (0 <= t1 && t1 <= 1)q[cnt++] = lerp(a, b, t1);
	}
	q[cnt++] = b;
	db s = 0;
	for (int i = 1; i < cnt; ++i) {
		Pd z = (q[i - 1] + q[i]) * 0.5;
		if (abs2(z - c.c) <= c.r * c.r)
			s += abs(cross(q[i - 1] - c.c, q[i] - c.c)) * 0.5;
		else
			s += c.r * c.r * get_angle(q[i - 1] - c.c, q[i] - c.c) * 0.5;
	}
	return s;
}

//圆与多边形相交的面积
db circle_int_polygon(circle C, Pd p[], int n) {
	db s = 0;
	p[n + 1] = p[1];
	for (int i = 1; i <= n; ++i)
		s += circle_int_triangle(C, p[i], p[i + 1]) * sgn(cross(p[i] - C.c, p[i + 1] - C.c));
	return abs(s);
}

db circle_cover(std::vector<Pd> v, Pd& o) {//最小圆覆盖,不得有重复点,时间复杂度O(N)
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(v.begin(), v.end(), g);
	db r2 = 0;
	for (int i = 0; i < v.size(); ++i) {
		if (abs2(v[i] - o) > r2) {
			o = v[i];
			r2 = 0;
			for (int j = 0; j < i; ++j) {
				if (abs2(v[j] - o) > r2) {
					o = (v[i] + v[j]) * 0.5;
					r2 = abs2(v[j] - o);
					for (int k = 0; k < j; ++k) {
						if (abs2(v[k] - o) > r2) {
							o = intersection(Ld((v[i] + v[j]) * 0.5, (v[i] - v[j]).rotate90()), Ld((v[i] + v[k]) * 0.5, (v[i] - v[k]).rotate90()));
							r2 = abs2(v[k] - o);
						}
					}
				}
			}
		}
	}
	return sqrt(r2);
}

int main(){

}