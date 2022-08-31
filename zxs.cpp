#include <bits/stdc++.h>

const int N = 1e5 + 10;
using namespace std;

int tot, n, m;
struct sst {
    int lson, rson, val;
} tre[N << 5];

int a[N], rt[N], len;

int build(int l, int r) {
    int root = ++tot;
    if (l == r)return root;
    int m = l + r >> 1;
    tre[root].lson = build(l, m);
    tre[root].rson = build(m + 1, r);
    return root;
}

int upd(int k, int l, int r, int root) {
    int dir = ++tot;
    tre[dir].lson = tre[root].lson, tre[dir].rson = tre[root].rson;
    tre[dir].val = tre[root].val+1;
    if (l == r)return dir;
    int m = l + r >> 1;
    if (k <= m)tre[dir].lson = upd(k, l, m, tre[dir].lson);
    else tre[dir].rson = upd(k, m + 1, r, tre[dir].rson);
    return dir;
}

int qry(int u, int v, int l, int r, int k) {
    int m = l + r >> 1;
    int x = tre[tre[v].lson].val - tre[tre[u].lson].val;
    if (l == r)return l;
    if (k <= x)return qry(tre[u].lson, tre[v].lson, l, m, k);
    else return qry(tre[u].rson, tre[v].rson, m + 1, r, k);
}

int main(int argc, char const *argv[]) {
    tot = 0;
    cin >> n >> m;
    vector<int> lsh;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        lsh.push_back(a[i]);
    }
    sort(lsh.begin(), lsh.end());
    lsh.erase(unique(lsh.begin(), lsh.end()), lsh.end());
    build(1, lsh.size());
    auto getId = [](vector<int> &lsh, int i) {
        return int(lower_bound(lsh.begin(), lsh.end(), a[i]) - lsh.begin() + 1);
    };
    for (int i = 1; i <= n; ++i) {
        rt[i] = upd(getId(lsh, i), 1, lsh.size(), rt[i - 1]);
    }
    while (m--) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << lsh[qry(rt[l - 1], rt[r], 1, lsh.size(), k) - 1] << endl;
    }
    return 0;
}