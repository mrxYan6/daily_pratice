//
// Created by mrx on 2022/4/28.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;
const int N = 1e5 + 100;


struct Trie {
	int cnt;
	Trie *nxt[26]{};
	Trie *fail{};
	vector<Trie *> G;
	bool flag;
	int pos;

	Trie() {
		cnt = 0;
		flag = false;
		for (auto &x: nxt)x = nullptr;
		pos = -1;
	}

	~Trie() {
		for (auto &x: nxt)delete x;
	}
};

void clear(Trie *root) {
	for (auto x: root->nxt) {
		if (x != nullptr) {
			clear(x);
		}
	}
	root->flag = false;
}

vector<Trie *> good;

int insert(Trie *root, const string &s, int i) {
	Trie *p = root;
	for (auto x: s) {
		int id = x - 'a';
		if (p->nxt[id] == nullptr) {
			p->nxt[id] = new Trie;
		}
		p = p->nxt[id];
	}
	if (p->flag)return p->pos;
	good.push_back(p);
	p->flag = true;
	p->pos = i;
	return p->pos;
}

void build(Trie *root) {
	queue<Trie *> Q;
	Trie *p = root;
	root->fail = nullptr;
	Q.push(p);
	while (!Q.empty()) {
		p = Q.front();
		Q.pop();
		for (int i = 0; i < 26; ++i) {
			if (p->nxt[i] != nullptr) {
				if (p == root) {
					p->nxt[i]->fail = p;
				} else {
					Trie *tmp = p->fail;
					while (tmp != nullptr) {
						if (tmp->nxt[i] != nullptr) {
							p->nxt[i]->fail = tmp->nxt[i];
							break;
						}
						tmp = tmp->fail;
					}
					if (tmp == nullptr)p->nxt[i]->fail = root;
				}
				p->nxt[i]->fail->G.push_back(p->nxt[i]);
				Q.push(p->nxt[i]);
			}
		}
	}
}

void qry(Trie *root, string &s) {
	Trie *p = root;
	for (auto x: s) {
		int id = x - 'a';
		while (p->nxt[id] == nullptr && p != root)p = p->fail;
		p = p->nxt[id];
		if (p == nullptr)p = root;
		Trie *tmp = p;
		if (tmp != root) {
			tmp->cnt++;
		}
	}
}

void dfs(Trie *rt) {
	for (auto x: rt->G) {
		dfs(x);
		rt->cnt += x->cnt;
	}
}


int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif
	Trie AC;
	int n;
	cin >> n;
	vector<int> mp(n);
	vector<int> ans(n);
	for (int i = 0; i < n; ++i) {
		string m;
		cin >> m;
		mp[i] = insert(&AC, m, i);
	}
	build(&AC);
	string s;
	cin >> s;
	qry(&AC, s);
	dfs(&AC);
	for (auto x: good)ans[x->pos] = x->cnt;
	for (int i = 0; i < n; ++i)cout << ans[mp[i]] << endl;
	return 0;
}