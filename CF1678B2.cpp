#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
const int N = 2e5 + 100;

pair<int, int> dp[N][2];//i位结尾为0/1,
//first -> num of opt,second -> num of str

template<class Ty1, class Ty2>
inline const pair<Ty1, Ty2> operator+(const pair<Ty1, Ty2> &p1, const pair<Ty1, Ty2> &p2) {
    pair<Ty1, Ty2> ret;
    ret.first = p1.first + p2.first;
    ret.second = p1.second + p2.second;
    return ret;
}

void sol() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = ' ' + s;
    for (int i = 1; i <= n; ++i)s[i] -= '0';
    for (int i = 0; i <= n; ++i)dp[i][0] = dp[i][1] = {1e9, 1e9};
    dp[0][0] = dp[0][1] = {0, 1};
    for (int i = 2; i <= n; i += 2) {
        dp[i][0] = min(
                {dp[i][0], dp[i - 2][1] + make_pair(s[i] + s[i - 1], 1), dp[i - 2][0] + make_pair(s[i] + s[i - 1], 0)});
        dp[i][1] = min({dp[i][1], dp[i - 2][1] + make_pair((!s[i]) + (!s[i - 1]), 0),
                        dp[i - 2][0] + make_pair((!s[i]) + (!s[i - 1]), 1)});
    }
    cout << min(dp[n][0], dp[n][1]).first << ' ' << min(dp[n][0], dp[n][1]).second << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        sol();
    }
}