#include<bits/stdc++.h>

using namespace std;

int arr[355];
int dp[55][55][55][55];//1,2,3,4个卡片用了多少张
int cnt[5];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i = 1;i <= n;++i)cin>>arr[i];
	memset(dp,0,sizeof dp);
	for(int i = 1;i <= m;++i){
		int x;
		cin>>x;
		cnt[x]++;
	}
	dp[0][0][0][0] = arr[1];
	for(int a = 0; a <= cnt[1] ;++a)
		for(int b = 0; b <= cnt[2] ;++b)
			for(int c = 0; c <= cnt[3] ;++c)
				for(int d = 0; d <= cnt[4] ;++d){
					int stp = a + 2 * b + 3 * c + 4 * d + 1;
					if(a) dp[a][b][c][d]=max(dp[a][b][c][d],dp[a-1][b][c][d] + arr[stp]);
					if(b) dp[a][b][c][d]=max(dp[a][b][c][d],dp[a][b-1][c][d] + arr[stp]);
					if(c) dp[a][b][c][d]=max(dp[a][b][c][d],dp[a][b][c-1][d] + arr[stp]);
					if(d) dp[a][b][c][d]=max(dp[a][b][c][d],dp[a][b][c][d-1] + arr[stp]);					
				}
	cout<<dp[cnt[1]][cnt[2]][cnt[3]][cnt[4]]<<endl;
}