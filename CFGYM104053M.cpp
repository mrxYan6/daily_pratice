//
// Created by mrx on 2022/11/16.
//
//
// Created by Victor Chen on 2022/11/16.
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


using i64 = long long;
const i64 mod = 1e9 + 7;

i64 power(i64 a, i64 b) {
	i64 res = 1;
	for (; b; b >>= 1, a = a * a % mod) if (b & 1)res = res * a % mod;
	return res;
}

i64 inv(i64 a) {
	return power(a, mod - 2);
}

void sol() {
	i64 n, m;
	int k;
	std::cin >> n >> m >> k;

	std::vector<std::vector<i64>> C(k + 1, std::vector<i64>(k + 1));
	C[0][0] = 1;
	for (int i = 1; i <= k; ++i) {
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j) {
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
		}
	}

	auto get = [&](i64 x) {
		std::vector<int> res;
//		do {
//			res.push_back(x & 1);
//			x >>= 1;
//		} while (x);
//		std::reverse(res.begin(), res.end());
		if (!x)res.emplace_back(x);
		while (x) {
			res.emplace_back(x & 1);
			x >>= 1;
		}
		return res;
	};

	auto b = get(n);
	auto a = get(m);


	i64 need = 0;

	while (b.size() > a.size()) {
		need = need * 2 + b.back();
		b.pop_back();
	}
	b.resize(a.size(), 0);

	std::vector dp(a.size() + 1, std::vector(k + 1, std::vector<i64>(k * k + 1)));
	std::vector vis(a.size() + 1, std::vector(k + 1, std::vector<int>(k * k + 1)));

//	pos ,limitcnt, cursum
	std::function<i64(int, int, int)> dfs = [&](int pos, int limit, int sum) -> i64 {
		if (pos == -1) return sum == 0;
		if (sum < 0)return 0;
		if (vis[pos][limit][sum])return dp[pos][limit][sum];
		vis[pos][limit][sum] = 1;
		auto& ans = dp[pos][limit][sum];
		ans = 0;
		if (a[pos] == 1) {
			for (int i = 0; i <= k - limit; ++i) {
				for (int j = 0; j <= limit; ++j) {
					int all = i + j;
					int nxt = sum * 2 + b[pos] - all * (k - all);
					if (nxt >= 0 && nxt <= k * k) {
						ans = (ans + dfs(pos - 1, limit + i, nxt) * C[k - limit][i] % mod * C[limit][j] % mod) % mod;
					}
				}
			}
		} else {
			for (int i = 0; i <= limit; ++i) {
				int all = i + k - limit;
				int nxt = sum * 2 + b[pos] - all * (k - all);
				if (nxt >= 0 && nxt <= k * k) {
					ans = (ans + dfs(pos - 1, limit, nxt) * C[limit][i] % mod) % mod;
				}
			}
		}
		return ans;
	};

	if (need > k * k) std::cout << 0 << '\n';
	else std::cout << dfs(int(a.size()) - 1, 0, need) << '\n';
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	sol();

	return 0;
}