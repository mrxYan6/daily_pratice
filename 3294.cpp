#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <functional>


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
        times[cur]++;
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

    int cnt = 0;
    i64 ans = 0;
    void dfs1 (int rt) {
        int& cnt = times[rt];
        for (int i = 0; i < 26; ++i) {
            if (nxt[rt][i] != 0) {
                dfs1(nxt[rt][i]);
                cnt += times[nxt[rt][i]];
            }
        }
        std::sort(nxt[rt].begin(), nxt[rt].end(), [&](int a, int b) {
            return times[a] < times[b];
        });
    }
    void dfs (int rt, int top) {
        int dfn = 0;
        if (end[rt] != 0) {
            dfn = ++cnt;
            // std::cout << "end : " << rt << ' ' << top << ' ' << dfn << '\n';
            ans += dfn - top;
        }
        for (int i = 0; i < 26; ++i) {
            if (nxt[rt][i] != 0) {
                // std::cout << char (i + 'a') << '\n';
                // std::cout << rt << "->" << nxt[rt][i] << '\n';
                // std::cout << end[rt] << ' ' << dfn << ' ' << cnt << '\n';
                // std::cout << "ans : " << ans << ' ' << '\n';
                dfs(nxt[rt][i], dfn);
            }
        }
    } 

};

void solve() {
    int n;
    std::cin >> n;

    std::vector<std::string> str(n);
    for (auto &x : str) std::cin >> x;
    for (auto &x : str) std::reverse(x.begin(), x.end());

    trie T;
    for (auto x : str) {
        T.insert(x);
    }

    std::vector<std::vector<int>> G(T.end.size());
    std::function<void(int, int)> dfs = [&] (int rt, int top) {
        if (T.end[rt] != 0) {
            G[top].emplace_back(rt);
        }
        for (int i = 0; i < 26; ++i) {
            if (T.nxt[rt][i] != 0) {
                dfs(T.nxt[rt][i], T.end[rt] != 0 ? rt : top);
            }
        }
    };
    dfs(0, 0);

    
    std::vector<int> size(G.size());
    std::function<void(int)> get = [&] (int rt) {
        size[rt] = T.end[rt] != 0;
        for (auto x : G[rt]) {
            get(x);
            size[rt] += size[x];
        }
        std::sort(G[rt].begin(), G[rt].end(), [&](int a, int b) {
            return size[a] < size[b];
        });
    };

    get(0);
    int cnt = 0;
    i64 ans = 0;
    std::function<void(int)> get_ans = [&] (int rt) {
        int dfn = cnt++;
        for (auto x : G[rt]) {
            // std::cout << "R:" << rt << ' '<< x << ' ' << dfn << ' ' << cnt << '\n';
            ans += cnt - dfn;
            get_ans(x);
        }
    };
    get_ans(0);
    
    std::cout << ans << '\n';

}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();

    return 0;
}