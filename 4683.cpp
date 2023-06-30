#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

using i64 = long long;

std::vector<char> ans;

struct trie{
    std::vector<std::array<int, 26>> nxt;
    std::vector<bool> is_end;
    std::vector<int> most;

    trie() {
        nxt.reserve(1000000);
        is_end.reserve(1000000);
        most.reserve(1000000);
        nxt.push_back(std::array<int, 26>{});
        is_end.push_back(0);
        most.push_back(27);
        // std::cout << is_end.size() << '\n';
    }

    int NEW() {
        is_end.push_back(0);
        nxt.push_back(std::array<int, 26>{});
        most.push_back(27);
        return is_end.size() - 1;
    }

    void insert (const std::string &s) {
        int cur = 0;
        for (auto c : s) {
            int &nxt_cur = nxt[cur][c - 'a'];
            // std::cout << "!!!!" << nxt_cur << '\n';
            if (nxt_cur == 0) {
                nxt_cur = NEW();
                // std::cout << "!!2312!!" << nxt_cur << '\n';
            }
            cur = nxt_cur;
        }
        is_end[cur] = 1;
    }

    void mark (const std::string & s){
        int cur = 0;
        for (auto c : s) {
            most[cur] = c - 'a';
            cur = nxt[cur][c - 'a'];
        }
    }

    void out_put(int x) {
        if (is_end[x]) {
            ans.push_back('P');
        }

        for (int i = 0; i < 26; ++i) {
            if (nxt[x][i] == 0 || i == most[x]) continue;
            ans.push_back('a' + i);
            out_put(nxt[x][i]);
            ans.push_back('-');
        }

        if (most[x] < 26) {
            ans.push_back('a' + most[x]);
            out_put(nxt[x][most[x]]);
            ans.push_back('-');
        }
    }
};

void solve() {
    int n;
    std::cin >> n;

    std::vector<std::string> str(n);
    for (auto &x : str) std::cin >> x;

    std::sort(str.begin(), str.end(), [&](const std::string &a, const std::string &b) {
        return a.length() > b.length();
    });

    trie T;
    for (auto x : str) {
        T.insert(x);
    }

    T.mark(str[0]);

    // std::cout << "FUCK\n";
    T.out_put(0);

    while (ans.back() == '-') ans.pop_back();

    std::cout << ans.size() << '\n';
    for (auto x : ans) std::cout << x << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();

    return 0;
}