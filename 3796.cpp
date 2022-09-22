//
// Created by mrx on 2022/5/21.
//

#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

struct Trie {
    int cnt;
    Trie *nxt[26]{};
    Trie *fail{};
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

void insert(Trie *root, const string &s, int i) {
    Trie *p = root;
    for (auto x: s) {
        int id = x - 'a';
        if (p->nxt[id] == nullptr) {
            p->nxt[id] = new Trie;
        }
        p = p->nxt[id];
    }
    p->flag = true;
    p->pos = i;
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
                if (p == root)p->nxt[i]->fail = p;
                else {
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
                Q.push(p->nxt[i]);
            }
        }
    }
}

int maxn = 0;

void qry(Trie *root, string &s) {
    Trie *p = root;
    for (auto x: s) {
        int id = x - 'a';
        while (p->nxt[id] == nullptr && p != root)p = p->fail;
        p = p->nxt[id];
        if (p == nullptr)p = root;
        Trie *tmp = p;
        while (tmp != root) {
            if (tmp->flag) {
                tmp->cnt++;
                maxn = max(maxn, tmp->cnt);
            }
            tmp = tmp->fail;
        }
    }
}

vector<int> ans;

void dfs(Trie *rt) {
    if (rt->cnt == maxn)ans.push_back(rt->pos);
    for (auto &i: rt->nxt) {
        if (i != nullptr)
            dfs(i);
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
    int t;
    while (cin >> t && t) {
        string s[t];
        Trie AC;
        for (int i = 0; i < t; ++i) {
            cin >> s[i];
            insert(&AC, s[i], i);
        }
        build(&AC);
        string m;
        cin >> m;
        maxn = 0;
        ans.clear();
        qry(&AC, m);
        dfs(&AC);
        std::sort(ans.begin(), ans.end());
        cout<<maxn<<endl;
        for (auto x: ans)cout << s[x] << endl;
    }
    return 0;
}