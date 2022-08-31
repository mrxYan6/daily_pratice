#include <iostream>
#include <vector>
const int  N = 5050;
using namespace std;
void sol(){
	int n;
	cin>>n;
	std::vector<int> a(n+1);
	for(int i =1 ; i<= n ;++i){
		cin>>a[i];
	}
	vector<vector<int>>dp(n+1,vector<int>(n+1,0));
	for(int i = 1; i <= n;++i){
		for(int j = i + 1; j <= n; ++j){
			dp[i][j]=dp[i][j-1];
			if(a[j]<a[i])dp[i][j]++;
		}
	}
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= n;++j){
			dp[j][i]+=dp[j-1][i];
		}
	}
	long long  ans=0;
	for(int i = 1; i <= n; ++i){
		for(int j = i + 2; j <= n;++j){
			if(a[j]<a[i])continue;
			ans+=(dp[j-1][n]-dp[i][n])-(dp[j-1][j]-dp[i][j]);
		}
	}
	cout<<ans<<endl;
}

int main(int argc, char const *argv[])
{
	int t;
	cin>>t;
	while(t--)sol();	
	return 0;
}