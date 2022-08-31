#include <iostream>
const int N = 1005;
using namespace std;
char mp[N][N];
bool check(int i,int j){
	int cnt  = 0;
	cnt+=mp[i][j]=='#';
	cnt+=mp[i][j+1]=='#';
	cnt+=mp[i+1][j]=='#';
	cnt+=mp[i+1][j+1]=='#';
	return cnt != 3;
}
int dx[]={0,0,-1,1};
int dy[]={1,-1,0,0};
int n,m;
bool in(int x,int y){
	return x>0&&y>0&&x<=n&&y<=m;
}
void dfs(int x,int y){
	mp[x][y]='.';
	for(int dir = 0; dir < 4; ++dir){
		int nx = x + dx[dir],ny = y + dy[dir];
		if(in(nx,ny)&&mp[nx][ny]=='#')dfs(nx,ny);
	}
}
int main(){
	cin>>n>>m;
	for(int i = 1; i <= n; ++i)cin>>(mp[i]+1);
	for(int i = 1; i <= n-1; ++i){
		for(int j = 1; j <= m-1; ++j){
			if(!check(i,j)){
				cout<<"Bad placement."<<endl;
				return 0;
			}
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= m ;++j){
			if(mp[i][j]=='#'){
				dfs(i,j);
				ans++;
			}
		}
	}
	cout<<"There are "<<ans<<" ships."<<endl;

}	