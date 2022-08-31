#include<cstdio>
#include<iostream>

#define ll long long
#define endl '\n'
using namespace std;
const int N = 1e5 + 5;
int n, to[N], in[N], dp[N], dpt[N], mk[N];
bool ring[N], ins[N];

int dfs(int x) {
    int t = to[x];
    ring[x] = ins[x] = 1;
    if (!ring[t]) {
        dpt[t] = dpt[x] + 1;
        dp[x] = dfs(t);
        dp[x] += (mk[t] ? (mk[x] = (mk[x] != 2 ? 1 : 0), 0) : 1);
    } else if (ins[t])dp[x] = dpt[x] - dpt[t] + 1, mk[x] = 1, mk[t] = (x == t ? 0 : 2);
    else dp[x] = dp[t] + 1;
    ins[x] = 0;
    return dp[x];
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
    ios::sync_with_stdio(false);
    cin >> n;
    int x;
    for (int i = 1; i <= n; ++i)cin >> to[i], ++in[to[i]];
    for (int i = 1; i <= n; ++i)if (!in[i])dp[i] = 1, dfs(i);
    for (int i = 1; i <= n; ++i)if (!ring[i])dfs(i);//totally a cycle
    for (int i = 1; i <= n; ++i)cout << dp[i] << endl;
    return 0;
}