#include <algorithm>
#include <iostream>
#include <queue>
const int N = 550;

char mp[N][N];
bool vis[N][N];
int dx[]={0,0,-1,1};
int dy[]={1,-1,0,0};
int n,m;
bool in(int x,int y){
	return x > 0 && y > 0 && x <= n && y <= m;
}
int main(){
	std::cin>>n>>m;
	for(int i=1; i <=n ; ++i){
		std::cin>>(mp[i]+1);
	}
	std::queue<std::pair<int,int>>q;
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= m; ++j){
			if(mp[i][j]=='s'){
				q.emplace(i,j);
				vis[i][j]=1;
			}
		}
	}
	while(!q.empty()){
		auto x = q.front();
		q.pop();
		vis[x.first][x.second]=1;
		if(mp[x.first][x.second]=='g'){
			std::cout<<"Yes\n";
			return 0;
		}
		for(int dir = 0; dir < 4; ++dir){
			int nx = x.first + dx[dir],ny = x.second + dy[dir];
			if(in(nx,ny)&&mp[nx][ny]!='#'&&!vis[nx][ny]){
				q.emplace(nx,ny);
			}
		}
	}
	std::cout<<"No\n";
	return  0;
}