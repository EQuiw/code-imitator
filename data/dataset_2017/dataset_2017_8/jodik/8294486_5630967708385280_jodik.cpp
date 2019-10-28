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
#include <iomanip>

#define FOR(i, a, b) for(int i=(a);i<=(b);i++)
#define FORD(i, a, b) for(int i=(a);i>=(b);i--)
#define REP(i, b) for(int i=0;i<(b);i++)
#define ll long long
#define nl printf("\n")

// M_PI SI TREBA ODLOZIT

using namespace std;

typedef long double ld;

int main(){
    //string m;
    int t;
    ll d, n;
    cin>>t;
    for (int tt = 0; tt < t; tt++){
        cout<<"Case #"<<(tt+1)<<": ";
        cin>>d>>n;
        ld max_time = 0;
        ll di, ki;
        REP(i, n){
            cin>>di>>ki;
            di = d - di;
            max_time = max((di/(ld)ki), max_time);
        }

        cout<<std::fixed<<std::setprecision(12)<<d/max_time<<endl;
    }
}