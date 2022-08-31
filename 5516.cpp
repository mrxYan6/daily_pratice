//
// Created by mrx on 2022/6/25.
//

#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
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
    string s;
    cin >> s;
    int wei[26];
    for (int i = 0; i < s.length(); ++i) {
        wei[s[i] - 'A']++;
    }
    int n = s.length();
    double tmp;
    for (int i = 0; i < n; ++i)for (int j = 0; j < n; ++j)cin >> tmp;

    return 0;
}