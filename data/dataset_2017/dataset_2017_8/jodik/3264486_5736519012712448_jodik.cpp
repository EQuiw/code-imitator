#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <array>
#include <algorithm>
#include <cmath>
#include <complex>
#include <map>
#include <cassert>
#include <functional>
#include <stdarg.h>

#define FOR(i, a, b) for(int i=(a);i<=(b);i++)
#define FORD(i, a, b) for(int i=(a);i>=(b);i--)
#define REP(i, b) for(int i=0;i<(b);i++)
#define ll long long
#define nl printf("\n")

// M_PI SI TREBA ODLOZIT

using namespace std;

typedef long double ld;

char opposite(char c){
    if(c=='-')
        return '+';
    else
        return '-';
}

int main(){
    string m;
    int t, k;
    cin>>t;
    for (int tt = 0; tt < t; tt++){
        cin>>m>>k;

        //cout<<m<<endl;
        int sol = 0;
        REP(i, m.size() - k + 1){
            if(m[i]=='-'){
                sol++;
                FOR(j, i, i+k-1){
                    m[j]=opposite(m[j]);
                }
            }
        }
        bool je = true;
        REP(i, m.size()){
            if(m[i]=='-'){
                cout<<"Case #"<<(tt+1)<<": IMPOSSIBLE\n";
                je = false;
                break;
            }
        }
        if(je)
            cout<<"Case #"<<(tt+1)<<": "<<sol<<endl;
    }
}