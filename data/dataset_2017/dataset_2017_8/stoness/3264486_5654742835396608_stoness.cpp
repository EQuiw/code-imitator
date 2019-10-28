//
//  main2017.cpp
//  Codejam2015
//
//  Created by stoness on 17/4/8.
//  Copyright © 2017年 sts. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <bitset>
#include <list>

#define check_bit(var,pos) ((var) & (1<<(pos)))

using namespace std;

int p1()  {
    string str;
    int n(0),res(0),i(0);
    cin>>str>>n;
    for (i=0;i<=str.length()-n;++i)  {
        if (str[i]=='+') continue;
        ++res;
        for (int j(0);j<n;++j) str[i+j]=(str[i+j]=='-'?'+':'-');
    }
    for (;i<str.length();++i)  {
        if (str[i]=='-') return -1;
    }
    return res;
}

int p2(char *cstr)  {
    string str;
    size_t len(0);
    bool rev(false);
    int i(1);
    cin>>str;
    len=str.copy(cstr, 20);
    while (i<len) {
        if (cstr[i]=='0') {rev=true; break;}
        if (cstr[i-1]>cstr[i]) {rev=true; break;}
        ++i;
    }
    if (rev)  {
        rev=false;
        while (i>0) {
            --i;
            --cstr[i];
            if (i==0) break;
            if (cstr[i-1]<=cstr[i]) break;
        }
        for (++i; i<len; ++i) {
            cstr[i]='9';
        }
        if (cstr[0]=='0') return 1;
    }
    return 0;
}

int p3(unsigned long long &ma, unsigned long long &mi)  {
    unsigned long long k(0),n(0);
    int kl(0);
    cin>>n>>k;
    for (unsigned long long j(k);j!=0; j>>=1) {
        kl++;
    }
    ma=n>>kl;
    if (ma==0) { mi=0; return 0; }
    if ( check_bit(n, kl-1) != 0 ) mi=ma;
    else mi=ma-1;
    if (kl==1) return 0;
    k-=(1<<(kl-1));
    if ( k > (n&((1<<(kl-1))-1)) )  {
        unsigned long long tmp(mi);
        mi=ma-1;
        ma=tmp;
    }
    
    return 0;
}

int main(int argc, const char * argv[]) {
    int T(0);
    int r1(0);
    unsigned long long ma(0),mi(0);
    char cstr[1024]={0};
    cin>>T;
    for (int i=0;i<T;++i) {
        memset(cstr, 0, 1024);
        r1=p3(ma,mi);
        cout<<"Case #"<<i+1<<": "<<ma<<' '<<mi<<endl;
        //if (r1<0) cout<<"IMPOSSIBLE"<<endl;
        //else      cout<<r1<<endl;
    }
    return 0;
}
