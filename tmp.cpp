#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <queue>
#include <array>
#include <map>
#include <set>

using i64 = long long;
int a;

class A {
public:
	int a;
	int b;

	A() { a = 1, b = 3; }

	int get() {
		return a;
	}
};

class B : public A {
public:
	int a;

	B() : A() {
		a = 2;
	}

	int get() {
		return a;
	}

	void print() {
		std::cout << ::a << '\n';
	}

};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	B x, y;
//	x.print();

	B* ptr = &x;
	x.a = 3;
	ptr->print();

	ptr = &y;
	ptr->print();
	return 0;
}