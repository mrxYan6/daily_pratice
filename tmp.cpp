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

struct tree {
	char nod;
	tree* lson, * rson;

	tree(char x) {
		nod = x;
		lson = rson = nullptr;
	}

	void build() {
		char x;
		std::cin >> x;
		if (x != '#') {
			lson = new tree(x);
			lson->build();
		}
		std::cin >> x;
		if (x != '#') {
			rson = new tree(x);
			rson->build();
		}
	}

	void pref() {
		std::cout << nod;
		if (lson != nullptr)lson->pref();
		if (rson != nullptr)rson->pref();
	}


	void mid() {
		if (lson != nullptr)lson->mid();
		std::cout << nod;
		if (rson != nullptr)rson->mid();
	}

	void suf() {
		if (lson != nullptr)lson->suf();
		if (rson != nullptr)rson->suf();
		std::cout << nod;
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	char x;
	std::cin >> x;
	tree t(x);
	t.build();

	t.pref();
	std::cout << '\n';
	t.mid();
	std::cout << '\n';
	t.suf();
	std::cout << '\n';
	return 0;
}