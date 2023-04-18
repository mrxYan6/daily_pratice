//
// Created by mrx on 2023/3/28.
//
#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <queue>
#include <array>
#include <map>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    std::map<std::string, int> map;
    int id = 0;
//    std::vector<std::vector<std::string>> str(n);

    std::vector<std::string> keys;
    std::vector<std::vector<int>> adj;
    std::vector<int> in;

    std::vector<std::string> prev;
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        std::vector<std::string> cur;
        auto ins = [&](const std::string& str) {
            if (!map.count(str)) {
                map[str] = id++;
                in.push_back(0);
                adj.emplace_back();
                keys.push_back(str);
            }
            cur.push_back(str);
        };
        int pos = 0;
        for (int j = 0; j < s.size(); ++j) {
            if (s[j] == '.') {
                ins(s.substr(pos, j - pos));
                pos = j + 1;
            }
        }
        ins(s.substr(pos, s.length() - pos));
//        str[i] = cur;
        if (i) {
            if (prev.size() == cur.size()) {
                for (int j = 0; j < cur.size(); ++j) {
                    if (cur[j] != prev[j]) {
                        adj[map[prev[j]]].push_back(map[cur[j]]);
                        in[map[cur[j]]]++;
                        break;
                    }
                }
            }
        }
        prev = cur;
    }
    auto cmp = [&keys](int i, int j) -> bool { return keys[i] > keys[j]; };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> q(cmp);
    for (int i = 0; i < id; ++i) {
        if (in[i] == 0) {
            q.push(i);
        }
    }
    std::vector<std::string> ans;
    while (!q.empty()) {
        auto cur = q.top();
        ans.push_back(keys[cur]);
        q.pop();
        for (auto v: adj[cur]) {
            in[v]--;
            if (in[v] == 0)q.push(v);
        }
    }
    for (int i = 0; i < id; ++i) {
        std::cout << ans[i] << ".\n"[i == id - 1];
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}