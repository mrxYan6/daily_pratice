#include <bits/stdc++.h>

int main(){
	int n,q;
	std::cin>>n>>q;
	std::vector<int>w(n+1);
	std::vector<int>in(n+1),out(n+1);
	std::vector<std::pair<int,int>>G[n+1];
	for(int i =1 ;i <= n;++i){
		int uu,ww;
		std::cin>>uu>>ww;
		if(uu)
		w[i]=uu;
	else w[i]=-ww;
	}
	for(int i = 0; i < q; ++i){
		int u,v,ww;
		std::cin>>u>>v>>ww;
		G[u].emplace_back(v,ww);
		in[v]++;
		out[u]++;
	}

	std::queue<int>Q;
	for(int i = 1; i <= n; ++i){
		if(in[i]==0)Q.push(i);
	}
	while(!Q.empty()){
		auto now = Q.front();
		Q.pop();
		if(w[now]<0)w[now]=0;
		for(auto x : G[now]){
			int v = x.first;
			int ww = x.second;
			in[v]--;
			if(in[v]==0)Q.push(v);
			w[v] += ww * w[now];
		}
	}

	bool flag = false;
	for(int i = 1;i <= n;++i){
		if(out[i]==0&&w[i]>0){
			flag = true;
			std::cout<<i<<' '<<w[i]<<std::endl;
		}
	}
	if(!flag)std::cout<<"NULL\n";
}
/*
5 6
1 0
1 0
0 1
0 1
0 1
1 3 1
1 4 1
1 5 1
2 3 1
2 4 1
2 5 1
*/