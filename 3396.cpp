c#include <bits/stdc++.h>

using namespace std;
const int N = 150010;

int ans[400][400];//mod,rem
int v[N];
int main(){
	int n ,m;
	cin>>n>>m;
	int block = sqrt(n);
	for(int i = 1; i <= n ;++i){
		cin>>v[i];
	}
	for(int i = 1; i <= n ;++i){
		for(int j = 1; j <= block; ++j){
			ans[j][i%j]+=v[i];
		}
	}
	for(int i = 1; i <= m; ++i){
		char cmd;
		cin>>cmd;
		if(cmd=='A'){
			int x,y;
			cin>>x>>y;
			if(x<=block){
				cout<<ans[x][y%x]<<endl;
			}
			else {
				int ans = 0;
				for(int i = y; i <= n; i += x){
					ans+=v[i];
				}
				cout<<ans<<endl;
			}
		} else {
			int x,y;
			cin>>x>>y;
			for(int j = 1; j <= block; ++j){
				ans[j][x % j]=ans[j][x % j]-v[x]+y;
			}
			v[x]=y;
		}
	}
	return  0;
}


/*
10 5
1 2 3 4 5 6 7 8 9 10
A 2 1
C 1 20
A 3 1
C 5 1
A 5 0
*/