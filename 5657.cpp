//
// Created by mrx on 2022/9/3.
//
#include<bits/stdc++.h>

int main(){
    int n;
    unsigned long long k;
    std::cin >> n >> k;
    unsigned long long ge = k ^ (k >> 1);
    for(int i = n - 1; i >= 0; --i){
        std::cout << ((ge >> i) & 1);
    }
}