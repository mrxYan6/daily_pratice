#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#define PI acos(-1.0)
double x0,Y0,x1,Y1;

struct nod{
	double x, y;

	nod(int x=0,int y=0):x(x),y(y){}
};

double radius[10];

int main(){
#ifndef ONLINE_JUDGE
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
#endif
	int n;
	std::vector<int> permu;
	std::vector<nod> rond;
	std::cin>>n;
	for(int i=0; i<n;++i){
		permu.push_back(i+1);
	}
	std::cin>>x0>>Y0>>x1>>Y1;
	double are = abs(x0-x1)*abs(Y0-Y1);
	for(int i = 1; i <= n; ++i){
		int x,y;
		std::cin>>x>>y;
		rond.emplace_back(x,y);
	}
	// for(auto x:permu)std::cerr<<x<<' ';
	double ans = 0;
	while(next_permutation(permu.begin(), permu.end())){
		for(auto x:permu)std::cerr<<x<<' ';
		std::cerr<<std::endl;
		for(int i = 0;i <= n;++i){
			radius[i]=0;
		}
		double tmp = 0;
		for(int i = 0; i < n; ++i){
			auto now = rond[permu[i]-1];
			double rid = std::min({abs(now.x-x0),abs(now.x-x1),abs(now.y - Y0),abs(now.y - Y1)});
			for(int j = 0;j < n;++j){
				if(j == permu[i]-1||radius[j]==0)continue;
				double dis = sqrt((rond[j].x-now.x)*(rond[j].x-now.x)+(rond[j].y-now.y)*(rond[j].y-now.y));
				// std::cerr<<permu[i]-1<<" X: "<<now.x<<" Y: "<<now.y<<' '<<j<<" X: "<<rond[j].x<<" Y: "<<rond[j].y<<" Dis: "<<dis<<std::endl;
				rid = std::min(rid,std::max((double)0,dis - radius[j]));
			}
			radius[permu[i]-1] = rid;
			tmp += PI*rid*rid;
		}
		ans = std::max(ans,tmp);
	}
	std::cout<<(long long)(are-ans+0.5)<<std::endl;
}

/*
2
20 0 10 10
13 3
17 7
*/