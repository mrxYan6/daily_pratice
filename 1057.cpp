#include <iostream>
#include <cstring>
using namespace std;
const int maxn=2e5+5;
using ll = long long;
ll a[maxn],b[maxn],c[maxn];
 
int main(){
	ll n,ans,sum;
	while(cin>>n){
		ans=sum=0;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(c,0,sizeof(c));
		for(ll i=1;i<=n;i++){
			cin>>a[i]>>b[i]>>c[i];
		}
		for(ll i=1;i<=n;i++){
			for(ll j=a[i];j<=b[i];j+=c[i]){
				ans^=j;
			}
		}
		if(ans){
			for(ll i=1;i<=n;i++){
				if(ans>=a[i]&&ans<=b[i]&&((ans-a[i])%c[i])==0) ++sum;
			}
			cout<<ans<<' ' <<sum<<endl;
		}
		else{
			cout<<"DC Qiang is unhappy.\n";
		}
		
	}
	return 0;
}

