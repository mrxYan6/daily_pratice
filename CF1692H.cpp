    //
    // Created by mrx on 2022/7/14.
    //
    #include <bits/stdc++.h>


    #define ll long long
    #define endl '\n'
    using namespace std;

    void sol() {
        int n;
        cin >> n;
        map<int, int> mp;
        vector<int> x(n + 1), ls(n + 1), l(n + 1), r(n + 1), f(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> x[i];
            ls[i] = mp[x[i]];
            mp[x[i]] = i;
        }
        int ans = 0, pos;
        for (int i = 1; i <= n; ++i) {
            if (f[ls[i]] - (i - ls[i] - 1) > 0) {
                f[i] = f[ls[i]] - (i - ls[i] - 1) + 1;
                l[i] = l[ls[i]];
            } else {
                f[i] = 1;
                l[i] = i;
            }
            if (f[i] > ans) {
                ans = f[i];
                pos = i;
            }
        }
        cout << x[pos] << ' ' << l[pos] << ' ' << pos << endl;
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
        cin >> t;
        while (t--) {
            sol();
        }
    }