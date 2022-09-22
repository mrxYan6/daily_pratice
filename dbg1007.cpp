#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

const int N = 1e6 + 1000;

void sol() {
    int n;
    cin >> n;
    vector<int> a(N, 0);
    int l = 1e7, r = 0;
    for (int i = 1; i <= n; ++i) {
        int pos, val;
        cin >> pos >> val;
        l = min(pos, l);
        r = max(r, pos);
        a[pos] += val;
    }
    vector<ll> sum(N, 0), sumsuf(N, 0);
    for (int i = l; i <= r; ++i) {
        sum[i] = sum[i - 1] + a[i];
    }
    for (int i = r; i >= l; --i) {
        sumsuf[i] = sumsuf[i + 1] + a[i];
    }
    ll lefcnt = 0, rigcnt = 0;
    for (int i = r; i >= l; --i) {
        rigcnt += 1ll * (i - l) * a[i];
    }
    ll ans = rigcnt;
    for (int i = l; i <= r; ++i) {
        lefcnt += sum[i];
        rigcnt -= sumsuf[i + 1];
        ans = min(ans, lefcnt + rigcnt);
    }
    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        sol();
    }
    return 0;
}