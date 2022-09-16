//
// Created by mrx on 2022/9/16.
//
#include <vector>
#include <algorithm>
#include <iostream>

using ll = long long;

struct ant {
	int pos, id, dir;
	bool turn;

	ant() {}

	ant(int pos, int id, int dir) : pos(pos), id(id), dir(dir), turn(false) {}
};

void sol() {
	int l, t, n;
	std::cin >> l >> t >> n;
	std::vector<ant> init(n), pos(n);
	for (int i = 0; i < n; ++i) {
		int p;
		char dir;
		std::cin >> p >> dir;
		init[i] = {p, i, dir == 'R' ? 1 : -1};
		pos[i] = init[i];
		pos[i].pos += t * pos[i].dir;
	}

	std::sort(init.begin(), init.end(), [&](const ant& lhs, const ant& rhs) {
		return lhs.pos < rhs.pos;
	});
	std::sort(pos.begin(), pos.end(), [&](const ant& lhs, const ant& rhs) {
		return lhs.pos < rhs.pos;
	});

	for (int i = 0; i < n; ++i) {
		if (i + 1 < n && pos[i + 1].pos == pos[i].pos) {
			pos[i].turn = pos[i + 1].turn = 1;
		}
		init[i].dir = pos[i].dir;
		init[i].pos = pos[i].pos;
		init[i].turn = pos[i].turn;
	}

	std::sort(init.begin(), init.end(), [&](const ant& lhs, const ant& rhs) {
		return lhs.id < rhs.id;
	});

	for (int i = 0; i < n; ++i) {
		if (init[i].turn) {
			std::cout << init[i].pos << " Turning\n";
		} else if (init[i].pos > l || init[i].pos < 0) {
			std::cout<<"Fell off\n";
		} else if (init[i].dir == 1) {
			std::cout << init[i].pos << " R\n";
		} else {
			std::cout << init[i].pos << " L\n";
		}
	}
}

int main() {
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
#endif
#ifndef LOCAL
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
#endif
	int t;
	std::cin >> t;
	for (int i = 1; i <= t; ++i) {
		std::cout << "Case #" << i << ":\n";
		sol();
		std::cout << '\n';
	}
	return 0;
}