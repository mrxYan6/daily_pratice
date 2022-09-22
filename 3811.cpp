#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 3e6+100;


int inv[N];

int main(){
	int n, p;
	cin>>n>>p;
	inv[1]=1;
	for(int i = 2; i <= n; ++i){
		inv[i] = (p - p / i)*inv[p%i]%p;
	}
	for(int i = 1; i <= n; ++i)cout<<inv[i]<<endl;
	return 0;
}
