//
// Created by mrx on 2022/4/22.
//


#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;
int n;
vector<int> ans;
int a[1010];

void dfs1(int l, int r) {
    if (l > r)return;
    int L, R;
    for (L = l + 1; L <= r && a[l] > a[L]; ++L);
    for (R = L + 1; R <= r && a[l] <= a[R]; ++R);
    if (L > l + 1)
        dfs1(l + 1, L - 1);
    if (L < r + 1)
        dfs1(L, R - 1);
    ans.push_back(a[l]);
}

void dfs2(int l, int r) {
    if (l > r)return;
    int L, R;
    for (L = l + 1; L <= r && a[l] <= a[L]; ++L);
    for (R = L + 1; R <= r && a[l] > a[R]; ++R);
    if (L > l + 1)
        dfs2(l + 1, L - 1);
    if (L < r + 1)
        dfs2(L, R - 1);
    ans.push_back(a[l]);
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
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    dfs1(1, n);
    if (ans.size() == n) {
        cout << "YES\n";
        cout << ans[0];
        for (int i = 1; i < n; ++i)cout << ' ' << ans[i];
        cout << endl;
        return 0;
    }
    ans.clear();
    dfs2(1, n);
    if (ans.size() == n) {
        cout << "YES\n";
        cout << ans[0];
        for (int i = 1; i < n; ++i)cout << ' ' << ans[i];
        cout << endl;
        return 0;
    }
    cout << "NO\n";
    return 0;
}