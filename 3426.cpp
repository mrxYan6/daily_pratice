//
// Created by mrx on 2022/6/27.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

vector<int> nxt(string &s) {
    int n = s.length() - 1;
    vector<int> nxt(n + 1);
    for (int i = 2, j = 0; i <= n; ++i) {
        while (j && s[i] != s[j + 1])j = nxt[j];
        if (s[i] == s[j + 1])j++;
        nxt[i] = j;
    }
    return nxt;
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
    string s;
    cin >> s;
    int n = s.length();
    s = '*' + s;
    vector<int> kmp = nxt(s), pre(n + 1), len(n + 1);
    for (int i = 1; i <= n; ++i) {
        len[i] = i;
        if (pre[len[kmp[i]]] >= i - kmp[i]) len[i] = len[kmp[i]];
        pre[len[i]] = i;
    }
    cout << len[n] << endl;
    return 0;
}