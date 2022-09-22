//
// Created by mrx on 2022/4/16.
//

#include <bits/stdc++.h>

#define ll long long
using namespace std;
int a[10];

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif
    double n = 0;

    for (int i = 0; i < 7; ++i) {
        cin >> a[i];
        n += a[i];
    }
    sort(a,a+7);
    double ans = 1.0 * (n - 6);
    for (int i = 0; i < 7; i++) ans /= double(n - i);
    for (int i = 0; i < 7; i++) ans *= a[i];
    for (int i = 1; i <= 7; i++) ans *= i;
    if(n<7||a[0]==0)ans=0;
    cout <<fixed<<setprecision(3)<< ans << endl;
    return 0;
}