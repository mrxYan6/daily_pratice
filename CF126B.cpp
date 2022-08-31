#include <bits/stdc++.h>

const int N = 1000000 + 100;
using namespace std;
char s[N];
int pre[N];

int main() {
    cin >> (s + 1);
    int len = strlen(s + 1);
    for (int i = 2, j = 0; i <= len; ++i) {
        while (j && s[j + 1] != s[i])j = pre[j];
        if (s[j + 1] == s[i])j++;
        pre[i] = j;
    }

    int xx = pre[len];
    if (xx == 0) {
        cout << "Just a legend\n";
    } else {
        for (int i = xx + 1; i < len; ++i) {
            if (pre[i] >= xx) {
                for (int j = 1; j <= xx; ++j)cout << s[j];
                cout << endl;
                return 0;
            }
        }
        if (pre[xx] != 0) {
            for (int i = 1; i <= pre[xx]; ++i)cout << s[i];
            cout << endl;
        } else
            cout << "Just a legend\n";
    }
    return 0;
}