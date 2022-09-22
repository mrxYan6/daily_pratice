#include <iostream>
#include <algorithm>
#include <cmath>
#include <chrono>

#define ll long long

const int N = 1e6 + 100;
ll block;
ll h[N], tmp[N], tag[2010], n;
using namespace std;

void Sort(int x) {
    int l = min(x * block, n);
    int r = min(x * block + block, n);
    for (int i = l; i < r; ++i)tmp[i] = h[i];
    sort(tmp + l, tmp + r);
}

void modify(int l, int r, int c) {
    int lb = l / block, rb = r / block;
    if (lb == rb) {
        for (int i = l; i <= r; ++i) {
            h[i] += c;
        }
        Sort(lb);
        return;
    }
    for (int i = l; i < lb * block + block; ++i) h[i] += c;
    for (int i = rb * block; i <= r; ++i) h[i] += c;
    for (int i = lb + 1; i < rb; ++i) tag[i] += c;
    Sort(lb);
    Sort(rb);
}

int qry(int l, int r, int c) {
    int ans = 0, lb = l / block, rb = r / block;
    if (lb == rb) {
        for (int i = l; i <= r; ++i) {
            ans += h[i] + tag[lb] >= c;
        }
        return ans;
    }
    for (int i = l; i < lb * block + block; ++i) {
        ans += h[i] + tag[lb] >= c;
    }
    for (int i = rb * block; i <= r; ++i) {
        ans += h[i] + tag[rb] >= c;
    }
    for (int i = lb + 1; i < rb; ++i) {
//        cerr << i * block + block << ' ' << lower_bound(tmp + i * block, tmp + (i * block + block), c - tag[i]) - tmp<< endl;
        ans += i * block + block - (lower_bound(tmp + i * block, tmp + (i * block + block), c - tag[i]) - tmp);
    }
    return ans;
}

int main() {
//    freopen("in.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int q;
    cin >> n >> q;
    block = sqrt(n);
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
        tmp[i] = h[i];
    }
    for (int i = 0; i <= n / block; ++i) {
        Sort(i);
    }
    while (q--) {
        char opt;
        cin >> opt;
        if (opt == 'M') {
            int l, r, c;
            cin >> l >> r >> c;
            l--, r--;
            modify(l, r, c);
        } else {
            int l, r, c;
            cin >> l >> r >> c;
            l--, r--;
            cout << qry(l, r, c) << endl;
        }
    }

}