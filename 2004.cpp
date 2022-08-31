#include <iostream>

using namespace std;
const int N = 1e3+100;

int sum[N][N];

int main(){
	int n,m,c;
	cin>>n>>m>>c;
	for(int i = 1; i <= n; ++i){
		int s=0;
		for(int j = 1; j <= m; ++j){
			int x;
			cin>>x;
			s += x;
			sum[i][j] = sum[i-1][j] + s;
		}
	}
	int ans = -1e9;
	int xx,yy;
	for(int X = 0; X <= n - c; ++X){
		for(int Y = 0; Y <= m - c; ++Y){
			if(ans<=sum[X+c][Y+c]+sum[X][Y]-sum[X+c][Y]-sum[X][Y+c]){
				xx = X+1,yy = Y+1;
				ans=sum[X+c][Y+c]+sum[X][Y]-sum[X+c][Y]-sum[X][Y+c];
			}
		}
	}
	cerr<<ans<<endl;
	cout<<xx<<' '<<yy<<endl;
}
