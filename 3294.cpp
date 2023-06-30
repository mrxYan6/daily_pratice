#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

using i64 = long long;

std::vector<char> ans;

struct trie {
    std::vector<std::array<int, 26>> nxt;
    std::vector<int> end, times;

    trie() {
        nxt.reserve(1000000);
        end.reserve(1000000);
        times.reserve(1000000);
        nxt.push_back(std::array<int, 26>{});
        end.push_back(0);
        times.push_back(0);
    }

    int NEW() {
        end.push_back(0);
        nxt.push_back(std::array<int, 26>{});
        times.push_back(0);
        return end.size() - 1;
    }

    void insert (const std::string &s) {
        int cur = 0;
        for (auto c : s) {
            int &nxt_cur = nxt[cur][c - 'a'];
            if (nxt_cur == 0) {
                nxt_cur = NEW();
            }
            cur = nxt_cur;
        }
        // std::cout << s << "::RT" << cur << '\n';
        end[cur]++;
    }

    int find(const std::string s) {
        int cur = 0;
        for (auto c : s) {
            int &nxt_cur = nxt[cur][c - 'a'];
            if (nxt_cur == 0) {
                return 0;
            }
            cur = nxt_cur;
        }
        return end[cur] != 0;
    }

    int dfs (const std::string s, int rt, int pos, int modify, int t) {
        if (pos == s.length() && modify == 1 && times[rt] < t) {
            // std::cout << "!!!" << rt << '\n';
            times[rt] = t;
            return end[rt];
        }

        auto c = s[pos] - 'a';

        int ans = 0;

        if (modify == 0) ans += dfs(s, rt, pos + 1, 1, t); //delete

        for (int i = 0; i < 26; ++i) {
            if (nxt[rt][i] && i != c && modify == 0) {
                ans += dfs(s, nxt[rt][i], pos + 1, 1, t); //replace
                ans += dfs(s, nxt[rt][i], pos, 1, t); //insert
            }
        }
        
        if (nxt[rt][c] != 0) ans += dfs(s, nxt[rt][c], pos + 1, modify, t); //keep

        return ans;
    }

};

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> str(n);
    for (auto &x : str) std::cin >> x;

    trie T;
    for (auto x : str) {
        T.insert(x);
    }

    for (int i = 1; i <= m; ++i) {
        std::string s;
        std::cin >> s;
        if (T.find(s)) std::cout << -1 << '\n';
        else std::cout << T.dfs(s, 0, 0, 0, i) << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();

    return 0;
}