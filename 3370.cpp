#include<bits/stdc++.h>
using namespace std;
const int  N = 10000+100;
const int  mod1 = 1e9 + 9,mod2 = 1e9 + 7,p =2333;

int main(){
	int n;
	cin>>n;
	vector<pair<long long, long long >>v;
	for(int i = 0; i < n; ++i){
		string s;
		cin>>s;
		long long hash1=0,hash2=0;
		for(auto x : s){
			hash1 = (hash1 * p + x) % mod1;
			hash2 = (hash2 * p + x) % mod2;
		}
		v.emplace_back(hash1,hash2);
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()),v.end());
	cout<<v.size()<<endl;
}

/*
5
abc
aaaa
abc
abcc
12345
*/