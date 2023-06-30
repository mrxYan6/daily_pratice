#include <vector>
#include <algorithm>
#include <iostream>

void solve() {
    std::string s;
    std::cin >> s;

    //kmp代码
    int n = s.length();
    std::vector<int> next(n + 1);

    next[0] = -1;
    int i = 0, j = -1;
    while (i < n) {
        if (j == -1 || s[i] == s[j]) {
            ++i;
            ++j;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
    
}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

    solve();

	return 0;
}