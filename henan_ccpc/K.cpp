#include <vector>
#include <algorithm>
#include <iostream>
std::vector<int> minp, primes;

void sieve(int n) {
    minp.resize(n + 1);
    primes.clear();
    for (int i = 2; i <= n; ++i) {
        if (!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for (auto p: primes) {
            if (p * i > n)break;
            minp[i * p] = p;
            if (p == minp[i]) {
                break;
            }
        }
    }
}

void insert(std::vector<int>& a, int x){
	for(int i = 0; i + 1 < a.size(); ++i)
	if(minp[std::abs(a[i] - x)] == std::abs(a[i] - x) && minp[std::abs(a[i + 1] - x)] == std::abs(a[i + 1] - x)) {
		a.insert(a.begin() + i + 1, x);
		return;
	}
}

void solve() {
    int n;
	std::cin>>n;
    sieve(n);

	if(n<=4) {
		std::cout<<"-1\n";
	} else if(n == 5) {
		std::cout<<"1 3 5 2 4\n";
	} else if(n==6) {
		std::cout<<"1 3 5 2 4 6\n";
	} else if(n==7) {
		std::cout<<"1 3 5 2 7 4 6\n";
	} else if(n==8) {
		std::cout<<"1 3 5 2 7 4 6 8\n";
	} else {
        std::vector<int> ans;
        for (int i = 1; i <= n; i += 2) if(i != n - 1) ans.emplace_back(i);
        for (int i = n / 2 * 2; i >= 4; i -= 2) if (i != n - 1) ans.emplace_back(i);
        insert(ans, 2);
        insert(ans, n - 1);
        for(auto x : ans)std::cout << x << " ";
        std::cout << "\n";
    }
}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

    solve();

	return 0;
}