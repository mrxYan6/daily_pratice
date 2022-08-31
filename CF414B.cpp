#include <iostream>
#include <cstring>
const int N = 2020;
const int mod = 1e9+7;
using namespace std;
int dp[N][N];
int main(){
	int n,k;
	cin>>n>>k;
	memset(dp,0,sizeof dp);
	for(int i =1 ;i <=n ;++i)dp[i][1]=1;
	for(int i = 1; i <= n ;++i){
		for(int j = 1; j <= k; ++j){
			for(int k = 1; k * i <= n; ++k){
				dp[i*k][j+1]=(dp[i*k][j+1]+dp[i][j])%mod;
			}
		}
	}
	int ans=0;
	for(int i = 1; i <= n; ++i)(ans+=dp[i][k])%=mod;
	cout<<ans<<endl;
}