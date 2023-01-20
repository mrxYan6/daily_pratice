//
// Created by meiru on 2023/1/3.
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

struct nod {
	std::vector<nod*> nxt;
	int cnt, end;

	nod() : cnt(0), end(false), nxt(2, nullptr) {}

	~nod() {
		for (auto x: nxt)delete x;
	}

	nod* get(int x) {
		if (nxt[x] == nullptr)nxt[x] = new nod;
		return nxt[x];
	}
};

void ins(nod* ptr, std::vector<int>& str) {
	for (auto x: str) {
		ptr = ptr->get(x);
		ptr->cnt++;
	}
	ptr->end++;
}

int qry(nod* ptr, std::vector<int>& str) {
	bool ok = true;
	int ans = 0;
	for (auto x: str) {
		if (ptr->nxt[x] == nullptr) {
			ok = false;
			break;
		}
		ptr = ptr->nxt[x];
		ans += ptr->end;
	}
	if (ok)return ans + ptr->cnt - ptr->end;
	else return ans;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n, m;
	std::cin >> n >> m;
	nod* tree = new nod;
	for (int i = 0; i < n; ++i) {
		int l;
		std::cin >> l;
		std::vector<int> str(l);
		for (int j = 0; j < l; ++j) {
			std::cin >> str[j];
		}
		ins(tree, str);
	}

	for (int i = 0; i < m; ++i) {
		int l;
		std::cin >> l;
		std::vector<int> str(l);
		for (int j = 0; j < l; ++j)std::cin >> str[j];
		std::cout << qry(tree, str) << '\n';
	}

	return 0;
}