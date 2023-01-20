//
// Created by meiru on 2023/1/14.
//
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

void insert(Trie* root, const std::deque<char>& s) {
	Trie* p = root;
	for (auto x: s) {
		int id = x - 'a';
		if (p->nxt[id] == nullptr) {
			p->nxt[id] = new Trie;
		}
		p = p->nxt[id];
	}
	p->end = s.size();
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
	std::deque<char> dq;

	Trie* root = new Trie;
	for (int i = 0; i < n; ++i) {
		if (s[i] == 'P')insert(root, dq);
		else if (s[i] == 'B')dq.pop_back();
		else dq.push_back(s[i]);
	}

}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	solve();

	return 0;
}