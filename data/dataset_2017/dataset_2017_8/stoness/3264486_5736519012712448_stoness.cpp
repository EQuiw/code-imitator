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

int main(int argc, const char * argv[]) {
    int T(0);
    int r1(0);
    cin>>T;
    for (int i=0;i<T;++i) {
        r1=p1();
        cout<<"Case #"<<i+1<<": ";
        if (r1<0) cout<<"IMPOSSIBLE"<<endl;
        else      cout<<r1<<endl;
    }
    return 0;
}
