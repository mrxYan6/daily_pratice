#include <iostream>

using namespace std;

using ll = long long;
const int N = 5e3+100;

ll a[N],dp[N][N];
ll q[N],pos[N];
int main(){
	int n, w, m;
	cin>>n>>w>>m;
	for(int i = 1; i <= n; ++i){
		cin>>a[i];
	}
	for(int i = 0; i <= n; ++i)for(int j = 0; j <= w; ++j)dp[i][j]=-1e18;
	//dp[i][j] = max{dp[i-1][k]+j*a[i]}
	//dp[i][j] = j * a[i] + max{dp[i-1][k]}(min(0,j-s-1)<=k<=j-1)
	dp[0][0] = 0;
	for(ll i = 1; i <= n;++i){
		ll l = 1,r = 1;
		q[l] = dp[i-1][w];
		pos[l] = w;
		for(ll j = w; j; --j){
			while(l <= r && pos[l] > j + m - 1)l++;
			while(l <= r && q[r] < dp[i-1][j-1])--r;
			pos[++r] = j - 1;
			q[r] = dp[i-1][j-1];
			// cout<<i<<' '<<j<<' '<<l<<' '<<r<<' '<<q[r]<<' '<<q[l]<<endl;
			dp[i][j] = q[l] + j * a[i];
		}
	}	
	ll tmp = -1e18;
	for(ll j = 0; j <= w; ++j){
		tmp = max(tmp, dp[n][j]);
	}
	cout<<tmp<<endl;
}