//
//  main2017b.cpp
//  Codejam2015
//
//  Created by stoness on 17/4/22.
//  Copyright © 2017年 sts. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <bitset>
#include <list>
#include <cmath>

#define check_bit(var,pos) ((var) & (1<<(pos)))

using namespace std;

double p1 ()  {
    long int d,n,k(0),s(0);
    int i(0);
    double ma(0),t(0);
    cin>>d>>n;
    for (i=0; i<n; ++i) {
        cin>>k>>s;
        t=(d-k)*1.0/s;
        ma=max(ma,t);
    }
    return d/ma;
}

int p2 ()  {
    int n,r,o,y,g,b,v;
    int i,j;
    char c1,c2,c3,c4,c5,c6;
    int q[7]={0};
    cin>>n>>r>>o>>y>>g>>b>>v;
    if (r>y+b || y>r+b || b>r+y)  {cout<<"IMPOSSIBLE"; return 0;}
    if (r>=max(y,b)) {c1='R'; q[1]=r;
        if (y>=b) {c2='Y';q[2]=y;c3='B';q[3]=b;}
        else      {c3='Y';q[3]=y;c2='B';q[2]=b;}
    } else if (y>=max(r,b)) {c1='Y'; q[1]=y;
        if (r>=b) {c2='R';q[2]=r;c3='B';q[3]=b;}
        else      {c3='R';q[3]=r;c2='B';q[2]=b;}
    } else   {c1='B'; q[1]=b;
        if (r>=y) {c2='R';q[2]=r;c3='Y';q[3]=y;}
        else      {c3='R';q[3]=r;c2='Y';q[2]=y;}
    }
    while (q[1]+q[2]+q[3]>0)  {
        if (q[1]>0) cout<<c1;
        if (q[2]>0) {
            cout<<c2;
            if (q[2]+q[3]-q[1]>0) {
                cout<<c3; if (q[3]>0) --q[3];}
            --q[2];
        } else if (q[3]>0) {
            cout<<c3; --q[3];
        }
        if (q[1]>0)--q[1];
    }
    return 0;
}

int e[128]={0},s[128]={0};
unsigned int d[101][101]={0};

double p3Calc(int n, int q, int u,int v)  {
    int dis[101]={0};
    int bk[101]={0};
    double res(0);
    int i,j;
    for (i=0;i<n;++i)
        ;
    return res;
}
int p3 ()  {
    int i,j,n,q,e[128]={0},s[128]={0};
    unsigned int d[101][101]={0};
    int u,v;
    char str[32]={0};
    cin>>n>>q;
    for (i=0;i<n;++i)
        cin>>e[i]>>s[i];
    for (i=0;i<n;++i)
        for (j=0;j<n;++j)
            cin>>d[i][j];
    for (i=0;i<q;++i) {
        cin>>u>>v;
        sprintf(str, "%.8lf",p3Calc(n,q,u,v));
        cout<<' '<<str;
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    int T(0);
    int r1(0);
    cin>>T;
    for (int i=0;i<T;++i) {
        //r1=p1();
        //printf("Case #%d: %.8lf\n",i+1,r1);
        cout<<"Case #"<<i+1<<": ";//<<r1<<endl;
        p2();cout<<endl;
        //if (r1<0) cout<<"IMPOSSIBLE"<<endl;
        //else      cout<<r1<<endl;
    }
    return 0;
}

