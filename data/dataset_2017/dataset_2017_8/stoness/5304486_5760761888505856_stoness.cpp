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
    int r,c,i,j;
    char csh[32][32]={0};
    cin>>r>>c;
    for (i=0;i<r;++i) for (int j=0;j<c;++j) cin>>csh[i][j];
    for (i=0;i<r;++i)  {
        char f='?';
        for (j=0; j<c; ++j) {
            if (csh[i][j]!='?') {f=csh[i][j]; break;}
        }
        if (f=='?') {
            continue;
        }
        for (j=0;j<c;++j)  {
            if (csh[i][j]!='?') f=csh[i][j];
            else csh[i][j]=f;
        }
        for (int k=i-1; k>=0; --k) {
            if (csh[k][0]=='?') memcpy(csh[k], csh[i], c);
            else break;
        }
    }
    for (int k=1;k<r;++k)
        if (csh[k][0]=='?') memcpy(csh[k], csh[k-1], c);
    for (i=0;i<r;++i)  {
        for (j=0;j<c;++j) cout<<csh[i][j];
        cout<<endl;
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    int T(0);
    int r1(0);
    cin>>T;
    for (int i=0;i<T;++i) {
        //r1=p1();
        cout<<"Case #"<<i+1<<": "<<endl;p1();
        //if (r1<0) cout<<"IMPOSSIBLE"<<endl;
        //else      cout<<r1<<endl;
    }
    return 0;
}
