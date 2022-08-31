#include<bits/stdc++.h>

struct nod{
	int x,y;
	nod(int x,int y):x(x),y(y){};
};

int dp[3000006];
std::vector<int> v[3000006];

int main(int argc, char const *argv[])
{
	int n;
	std::cin >> n;
	int maxn = 0;
	for(int i = 0; i < n; ++i){
		int x, y;
		std::cin >> x >> y;
		maxn = std::max(maxn, y);
		v[y].push_back(x-1);
	}
	memset(dp,0,sizeof dp);
	int ans = 0;
	for(int i = 1;i <= maxn;++ i){
		dp[i] = dp[i-1];
		for(auto x:v[i]){
			dp[i] = std::max(dp[i], dp[x] + i - x );
			std::cout<< i<<" :"<<dp[i]<<std::endl;
			ans = std::max(ans,dp[i]);
		}
	}

	std::cout<<ans<<std::endl;
	return 0;
}