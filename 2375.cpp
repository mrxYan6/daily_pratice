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
const int mod = 1e9 + 7;

void sol() {
	std::string s;
	std::cin >> s;
	int n = s.length();
	std::vector<int> prev(n + 1);
	std::vector<int> dep(n + 1);
	dep[1] = 1;
	for (int i = 1, j = 0; i < n; ++i) {
		while (j && s[i] != s[j])j = prev[j];
		j += s[i] == s[j];
		prev[i + 1] = j;
		dep[i + 1] = dep[j] + 1;
	}
	i64 ans = 1;
	for (int i = 1, j = 0; i < n; ++i) {
		while (j && s[i] != s[j])j = prev[j];
		j += s[i] == s[j];
		while (2 * j > i + 1)j = prev[j];
		ans = ans * (1 + dep[j]) % mod;
	}
	std::cout << ans << '\n';
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t;
	std::cin >> t;
	while (t--) {
		sol();
	}
	return 0;
}