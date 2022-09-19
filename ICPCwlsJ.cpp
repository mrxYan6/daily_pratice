//
// Created by mrx on 2022/9/18.
//
#include <algorithm>
#include <vector>
#include <iostream>
#include <stack>
using ll = long long;

long long gcd(long long a, long long b) {
	return a % b == 0 ? b : gcd(b, a % b);
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
//	int x, y;
//	std::cin >> x >> y;
//	int a = x * y - x * x + x - 2;
//	int b = -x * x + 2 * x - 2;
//	int g = gcd(a, b);
//	a /= g, b /= g;
//	std::cout << a << ' ' << b << '\n';
//	int fm = x * (x - 1) / 2;
//	for (int i = 1; i < x - 1; ++i) {
//		std::cout << 1 << ' ' << fm - i + 1 << '\n';
//	}
//	std::cout << "1 1\n";
	int n;
	using namespace std;
	vector<vector<int>> G(n, vector<int>());
	vector<bool> inStack(n, false);
	vector<int> dfn(n, -1), low(n, -1);
	vector<int> f(n), val(n), wei(n);
	stack<int> s;
	int id = 0, sccCnt = 0;
	std::function<void(int)> tarjan = [&](int u) -> void {
		low[u] = dfn[u] = id++;
		s.push(u), inStack[u] = true;
		for (auto v: G[u]) {
			if (dfn[v] == -1) {
				tarjan(v);
				low[u] = min(low[u], low[v]);
			} else if (inStack[v]) {
				low[u] = min(low[u], low[v]);
			}
		}
		if (dfn[u] == low[u]) {
			while (s.top() != u) {
				auto x = s.top();
				s.pop();
				inStack[x] = false;
				f[x] = sccCnt;
				val[sccCnt] += wei[x];
			}
			s.pop();
			inStack[u] = false;
			f[u] = sccCnt;
			val[sccCnt] += wei[u];
			sccCnt++;
		}
		return;
	};
	return 0;
}