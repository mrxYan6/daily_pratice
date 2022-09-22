//
// Created by mrx on 2022/9/13.
//
#include <bits/stdc++.h>

using ll = long long;

ll power(ll a, ll b, ll mod) {
    ll ans = 1;
    for (; b; b >>= 1, a = a * a % mod) if (b & 1)ans = a * ans % mod;
    return ans;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
#endif
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#endif
    std::string s;
    int n = 0;
    while (std::cin >> s && s != ".") {
        n++;
        std::cout << "Case " << n;

        auto check = [&](std::string &str) -> bool {
            std::vector<int> a, e;
            std::string poly = str.substr(1, str.find('/') - 2);
            int ptr = 0, n = poly.size();
            while (ptr < n) {
                int sig = 1;
                //sign
                if (poly[ptr] == '+') sig = 1, ptr++;
                if (poly[ptr] == '-') sig = -1, ptr++;

                //计算系数
                int digit = 0;
                while (ptr < n && isdigit(poly[ptr])) digit = digit * 10 + poly[ptr++] - '0';
                //常数
                if (ptr == n) {
                    a.push_back(digit);
                    e.push_back(0);
                } else {
                    ptr++;
                    if (digit == 0)digit = 1;
                    digit *= sig;
                    int pw = 0;
                    if (poly[ptr] == '^') {
                        ptr++;
                        //不为1次项k
                        while (ptr < n && isdigit(poly[ptr])) pw = pw * 10 + poly[ptr++] - '0';
                    } else pw = 1;
                    a.push_back(digit);
                    e.push_back(pw);
                }
            }

            int D = stoi(str.substr(str.find('/') + 1));
//            for (int i = 0; i < a.size(); ++i)std::cerr << a[i] << '^' << e[i] << ' ';
            std::cerr << '\n';
            for (int x = 1; x <= e[0] + 1; ++x) {
                ll ans = 0;
                for (int i = 0; i < a.size(); ++i) {
                    ans = (ans + a[i] * power(x, e[i], D) % D) % D;
                }
                if (ans)return false;
            }
            return true;
        };

        if (check(s))std::cout << ": Always an integer\n";
        else std::cout << ": Not always an integer\n";
    }
    return 0;
}