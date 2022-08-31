//
// Created by mrx on 2022/5/4.
//
#include <iostream>

#define ll long long
#define endl '\n'
using namespace std;

struct Trie {
    int sz;
    ll cnt, tag;
    Trie *nxt[2];

    Trie() {
        for (auto &i: nxt)i = nullptr;
        tag = 0;
    }

    inline void pushdown() {
        if (tag) {
            for (auto &v: nxt) {
                if (v) {
                    v->tag = tag;
                    v->cnt += v->sz * v->tag;
                }
            }
            tag = 0;
        }
    }

    inline void pushup() {
        cnt = 0;
        for (auto u: nxt)
            if (u)cnt += u->cnt;
    }

};

void ins(Trie *root, int w) {
    Trie *p = root;
    for (int i = 0; w; ++i) {
        int id = w & 1;
        if (p->nxt[id] == nullptr)p->nxt[id] = new Trie;
        p = p->nxt[id];
        w >>= 1;
    }
}


void qry(int w) {

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
    int n;

    return 0;
}