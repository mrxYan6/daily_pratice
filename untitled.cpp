#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+100;
std::vector<int> G[N];

int dpt[N],size[N],fa[N],son[N],top[N],NID[N],OID[N];
void dfs1(int u,int f){
	dpt[u]=dpt[f]+1,son[u]=0;
	fa[u]=f,size[u]=1;
	for(auto v : G[u])
	{
		if(v!=f){
			dfs1(v,u);
			size[u]+=size[v];
			if(size[son[u]]<size[v])son[u]=v;
		}
	}
}

void dfs2(int x,int topx){
	top[x]=topx;
	NID[x]=++t;
	OID[t]=x;
	if(son[x])dfs2(son[x],topx);
	for(auto v:G[x]){
		if(v==f[x]||v==son[x])continue;
		dfs2(v,v);
	}
}

#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define T t[rt]
#define LS t[rt<<1]
#define RS t[rt<<1|1]
struct seg
{
	int num,lazy,lc,rc;
	int l,r;
}t[N<<2];

int a[N];

inline pushup(int rt){
	T.c=LC.lc;
	T.rc=RS.rc;  
    int ans=LS.num+RS.num;  
    if(LS.rc == RS.lc)ans--;  
    T.num=ans;  
}

void build(int l,int r,int rt)
{
	T.l=l,T.r=r;
	if(l==r){
		T.num=T.lazy=0;
		T.lc=T.rc=a[l];
		return;
	}
	int m=l+r>>1;
	build(lson);
	build(rson);
	pushup(rt);
}

inline void pushdown(int rt)
{
	if(!T.lazy){
		RS.lazy=LS.lazy=T.lazy;
		LS.num=RS.num=1;
		LS.lc=RS.lc=T.lc;
		LS.rc=RS.rc=T.rc;
		T.lazy=0
	}
}

void modify(int c,int l,int r,int rt)
{
	if(T.l==l&&T.r==r){
		T.num=T.lazy=1;
		T.lc=T.rc=c;
		return;
	}
	pushdown(rt);

}


int main(int argc, char const *argv[])
{
	
	return 0;
}