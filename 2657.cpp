#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

#define endl '\n'
using namespace std;

vector<int> s;
int dp[12][12];

int dfs(int pos, int last, bool nolim, bool noqd0) {
    if (pos == s.size()) {
        return noqd0;
    }
    if (noqd0 && nolim && ~dp[s.size() - pos][last])return dp[s.size() - pos][last];
    int x = nolim ? 9 : s[pos];
    int ans = 0;
    for (int i = 0; i <= x; ++i) {
        if (abs(i - last) < 2)continue;
        int nxt = i;
        if (!noqd0 && i == 0) nxt = -2;
        ans += dfs(pos + 1, nxt, nolim || i < x, nxt != -2);
    }
    if (noqd0 && nolim)dp[s.size() - pos][last] = ans;
    return ans;
}

int work(int x) {
    s.clear();
    while (x) {
        s.push_back(x % 10);
        x /= 10;
    }
    std::reverse(s.begin(), s.end());
    return dfs(0, -2, false, false);
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
    int a, b;
    cin >> a >> b;
    memset(dp, -1, sizeof dp);
//    for (int i = 1; i <= 1000; i += 1)cerr << i << ' ' << work(i) << endl;
    cout << work(b) - work(a - 1) << endl;
    return 0;
}