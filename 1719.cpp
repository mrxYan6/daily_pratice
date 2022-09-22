#include<iostream>
using namespace std;

const int N = 125;

int sum[N][N],qz[N];

int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		int s = 0;
        for(int j=1;j<=n;j++){
        	int x;
        	cin>>x;
        	s+=x;
        	sum[i][j]=sum[i-1][j] + s;
        }
    }

	for(int i = 1; i <= n;++i){
		for(int j = 1; j <= n; ++j)cerr<<sum[i][j]<<' ';
			cerr<<endl;
	}
	int ans = -1e9 ;
	for(int x1 = 1; x1 <= n; ++x1){
		for(int y1 = 1; y1 <= n; ++y1){
			for(int x2 = x1; x2 <= n; ++x2){
				for(int y2 = y1; y2 <= n; ++y2){
					ans = max(ans,sum[x2][y2]-sum[x2][y1-1]-sum[x1-1][y2]+sum[x1-1][y1-1]);
				}
			}
		}
	}
	cout<<ans<<endl;
}