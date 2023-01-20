//
// Created by meiru on 2023/1/14.
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
#include <stack>

using i64 = long long;

struct Trie {
	int cnt;
	std::vector<Trie*> nxt;
	Trie* fail;
	int end;

	Trie() : nxt(26, nullptr), fail(nullptr), end(0), cnt(0) {}

	~Trie() { for (auto x: nxt)delete x; }
};


void clear(Trie* root) {
	for (auto x: root->nxt) {
		if (x != nullptr) {
			clear(x);
		}
	}
	root->end = 0;
}

void insert(Trie* root, const std::string& s) {
	Trie* p = root;
	for (auto x: s) {
		int id = x - 'a';
		if (p->nxt[id] == nullptr) {
			p->nxt[id] = new Trie;
		}
		p = p->nxt[id];
	}
	p->end = s.length();
	p->cnt++;
}

void build(Trie* root) {
	std::queue<Trie*> Q;
	Trie* p = root;
	root->fail = nullptr;
	Q.push(p);
	while (!Q.empty()) {
		p = Q.front();
		Q.pop();
		for (int i = 0; i < 26; ++i) {
			if (p->nxt[i] != nullptr) {
				if (p == root)p->nxt[i]->fail = p;
				else {
					Trie* tmp = p->fail;
					while (tmp != nullptr) {
						if (tmp->nxt[i] != nullptr) {
							p->nxt[i]->fail = tmp->nxt[i];
							break;
						}
						tmp = tmp->fail;
					}
					if (tmp == nullptr)p->nxt[i]->fail = root;
				}
				Q.push(p->nxt[i]);
			} else {
				if (p == root)p->nxt[i] = p;
				else p->nxt[i] = p->fail->nxt[i];
			}
		}
	}
}

void solve() {
	std::string s;
	std::cin >> s;

	int n;
	std::cin >> n;

	std::vector<std::string> words(n);
	Trie* tree = new Trie;
	for (int i = 0; i < n; ++i) {
		std::cin >> words[i];
		insert(tree, words[i]);
	}

	build(tree);

	auto p = tree;
	int m = s.length();
	std::vector<Trie*> pos(m + 1);
	std::vector<int> ans(m + 1);

	int ptr = 0;
	pos[0] = tree;
	for (int i = 0; i < m; ++i) {
		int id = s[i] - 'a';
		p = p->nxt[id];
		pos[++ptr] = p;
		ans[ptr] = i;
		if (p->end) {
			ptr -= p->end;
			if (ptr == 0)p = tree;
			else p = pos[ptr];
		}
	}
	for (int i = 1; i <= ptr; ++i) std::cout << s[ans[i]];
	std::cout << '\n';
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	solve();
	return 0;
}