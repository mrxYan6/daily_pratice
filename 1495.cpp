#include <iostream>
const int N = 11;
#define ll long long 
using namespace std;
ll a[N],m[N];

ll exgcd(ll aa,ll bb,ll &x,ll &y){
	if(bb == 0){
		x = 1,y = 0;
		return aa;
	}
	ll gcd = exgcd(bb, aa % bb, x, y);
	ll t = x;
	x = y;
	y = t - aa / bb * y;
	return gcd;
}

ll CRT(int n){
	ll LCM, gcd, X, xi, yi, c;
	X = a[0], LCM = m[0];
	for(int i = 1;i < n; ++i)
	{
		gcd = exgcd(LCM, m[i], xi, yi);
		c = a[i] - X;
		if(c%gcd)return -1;
		ll t = m[i] / gcd;
		xi = c / gcd * xi % t;
		X = LCM * xi + X;
		LCM = LCM / gcd * m[i];
		X %= LCM;
	}
	X = (X + LCM) % LCM;
	if(X == 0)X = LCM ;
	return X;
}

int main(){
	int n;
	cin>>n;
	for(int i = 0;i < n;++i){
		cin>>m[i]>>a[i];
	}
	cout<<CRT(n)<<endl;
}