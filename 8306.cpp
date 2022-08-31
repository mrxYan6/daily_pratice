//
// Created by mrx on 2022/5/17.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'

struct Trie {
    struct nod {
        int cnt;
        std::unordered_map<char, nod *> nxt;

        nod() {
            cnt = 0;
            nxt.clear();
        }
    };

    nod *root;

    Trie() {
        root = new nod;
    }

    void ins(std::string &s) {
        nod *p = root;
        for (auto x: s) {
            if (!p->nxt.count(x)) {
                p->nxt[x] = new nod;
            }
            p = p->nxt[x];
        }
    }
};

using namespace std;

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
    cin >> t;
    while (t--) {
        Trie trie;
    }
    return 0;
}
