#include <bits/stdc++.h>

using namespace std;

std::vector<int> h;

void up(int x)
{
    while(x>1&&h[x]>h[x/2]){
        swap(h[x],h[x/2]);
        x/=2;
    }
}

void down(int x){
    while(x * 2 <= n){
        t = x * 2;
        if(t + 1 <= n && h[t + 1] > h[t]) t++;
        if(h[t] <= h[x])break;
        swap(h[x],h[t]);
        z = t;
    }
}

int main(int argc, char const *argv[])
{
    int n;
    cin>>n;
    return 0;
}