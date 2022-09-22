#include <iostream>

const int N = 2000;
char s[N];

void build(int l,int r){
	if(r>l){
		build(l,(l+r)>>1);
		build((l+r+1)>>1,r);
	}
	bool B = 1,I = 1;
	for(int i = l; i <= r; ++i){
		if(s[i]=='1'){
            B=0;
        }else if(s[i]=='0'){
            I=0;
        }
	}
	if(B) std::cout<<"B";
	else if(I) std::cout<<"I";
	else std::cout<<"F";
}

int main(){
	int n;
	std::cin>>n;
	std::cin>>(s+1);
	build(1,(1<<n));
}