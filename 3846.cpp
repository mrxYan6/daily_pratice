//
// Created by mrx on 2022/9/15.
//
#include <bits/stdc++.h>

using ll = long long;

ll power(ll a, ll b, ll p) {
	ll ans = 1;
	for (; b; a = a * a % p, b >>= 1)if (b & 1)ans = ans * a % p;
	return ans;
}

ll bsgs(ll a, ll b, ll p) {
	std::map<ll, ll> hash;
	ll m = std::sqrt(p) + 0.5;
	ll cur = 1, inv = power(power(a, m, p), p - 2, p);
	for (int i = 0; i <= m; ++i) {
		if (!hash.count(cur))hash[cur] = i;
		cur = cur * a % p;
	}
	for (int i = 0; i <= m; ++i) {
		if (hash.count(b))return i * m + hash[b];
		b = b * inv % p;
	}
	return -1;
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
	ll p, b, n;
	std::cin >> p >> b >> n;
	ll ans = bsgs(b, n, p);
	if (ans == -1)std::cout << "no solution\n";
	else std::cout << ans << '\n';
	return 0;
}