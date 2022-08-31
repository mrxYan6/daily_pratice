#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
const int N = 1000000+1000;
const int mod = 100003;
std::vector<int> G[N];
int cnt[N],vis[N],dpt[N];
int n ,m;
bool in(int x,int y){
	return x>0 && y>0 && x<= n&& y<=m;
}
int main(){
	std::cin>>n>>m;
	for(int i = 0; i <= n;++i){
		G[i].clear();
		vis[i]=cnt[i]=dpt[i]=0;
	}
	for(int i = 0; i < m; ++i){
		int x,y;
		std::cin>>x>>y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	std::queue<int>q;
	q.push(1);
	cnt[1]=vis[1]=1;
	while(!q.empty()){
		auto x = q.front();
		q.pop();
		for(auto v : G[x]){
			if(!vis[v]){
				cnt[v]=cnt[x];
				dpt[v]=dpt[x]+1;
				vis[v]=1;
				q.push(v);
			}else if(dpt[v]==dpt[x]+1){
				cnt[v] = (cnt[v] + cnt[x])%mod;
			}
		}
	}
	for(int i = 1; i <= n; ++i)std::cout<<cnt[i]<<std::endl;
}
/*
5 7
1 2
1 3
2 4
3 4
2 3
4 5
4 5
*/