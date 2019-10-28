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

pair<ll,ll> separate(ll n){
    return make_pair(n/2, n/2 - (1-n%2));
};

pair<ll,ll> solve2(ll s1, ll n1, ll s2, ll n2, ll k){
   // printf("%lld %lld %lld %lld %lld\n", s1, n1, s2, n2, k);
   /* cout<<s1<<" ";
    cout<<n1<<" ";
    cout<<s2<<" ";
    cout<<n2<<" ";
    cout<<k<<" "<<endl;*/
    if(k <= n1){
        return separate(s1);
    }
    k -= n1;
    if(k <= n2) {
        return separate(s2);
    }
    k -= n2;
    
    ll new_n1, new_n2, new_s1, new_s2;
    pair<ll,ll> p1 = separate(s1);
    pair<ll,ll> p2 = separate(s2);

    new_s1 = max(p1.first, p1.second);
    new_s1 = max(new_s1, p2.second);
    new_s1 = max(new_s1, p2.first);

    new_s2 = min(p1.first, p1.second);
    new_s2 = min(new_s2, p2.second);
    new_s2 = min(new_s2, p2.first);

    new_n1 = 0;
    new_n2 = 0;

    if(p1.first == new_s1)
        new_n1+=n1;
    else
        new_n2+=n1;

    if(p1.second == new_s1)
        new_n1+=n1;
    else
        new_n2+=n1;

    if(p2.first == new_s1)
        new_n1+=n2;
    else
        new_n2+=n2;

    if(p2.second == new_s1)
        new_n1+=n2;
    else
        new_n2+=n2;

    return solve2(new_s1, new_n1, new_s2, new_n2, k);
};

pair<ll,ll> solve(ll n, ll k){
    if(k == 1){
        return separate(n);
    }
    else return solve2(separate(n).first, 1, separate(n).second, 1, k-1);
};

int main(){
    string m;
    ll t, n, k;
    cin>>t;
    for (int tt = 0; tt < t; tt++){
        cin>>n>>k;
        pair<ll,ll> p = solve(n,k);

        cout<<"Case #"<<(tt+1)<<": "<<p.first<<" "<<p.second<<endl;
    }
}