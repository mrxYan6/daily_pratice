#include <bits/stdc++.h>

using namespace std;
const int N = 1e6+100;
const long long mod = 666623333; 
long long A[N],phi[N], pri[N],cnt;
bool vis[N];

int main(){
	cnt=0;
	for(int i = 2; i <= 1e6; ++i){
		if(!vis[i])pri[++cnt]=i;
		for(int j = 1; j <= cnt && i * pri[j] <= 1e6;++j)
		{
			vis[i*pri[j]]=1;
			if(i%pri[j]==0)break;
		}
	}
	long long l,r;
	cn>>l>>r;
	long long ans=0;
	for (long long i = l; i <= r; i++)
		phi[i - l] = i, A[i - l] = i;
	for (int i = 1; i <= cnt && pri[i] * pri[i] <= r; i++)
	{
		long long pr = pri[i], start = l;
		if (l % pr) start = l / pr * pr + pr;
		for (long long j = start; j <= r; j += pr)
		{
			phi[j - l] = phi[j - l] / pr * (pr - 1);
			while(A[j - l] % pr == 0) A[j - l] /= pr;
		}
	} 
	for (long long i = l; i <= r; i++)
	{
		if(A[i - l] > 1)
			phi[i - l] = phi[i - l] / A[i - l] * (A[i - l] - 1);
		ans = (ans + (i - phi[i - l]) % mod) %mod;
	}
	cout<<ans<<endl;
}