#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctype.h>
#include <deque>
#include <queue>
#include <cstring>
#include <set>
#include <list>
#include <map>
#include <random>
#include <unordered_map>
#include <stdio.h>

using namespace std;

typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<bool> vb;
typedef std::vector<string> vs;
typedef std::vector<double> vd;
typedef std::vector<long long> vll;
typedef std::vector<std::vector<int> > vvi;
typedef vector<vvi> vvvi;
typedef vector<vll> vvll;
typedef std::vector<std::pair<int, int> > vpi;
typedef vector<vpi> vvpi;
typedef std::pair<int, int> pi;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;

const long long mod = 1000000007;

#define all(c) (c).begin(),(c).end()
#define sz(c) (int)(c).size()
#define forn(i, a, b) for(int i = a; i < b; i++)

#define pb push_back
#define mp make_pair

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    int t;
    cin>>t;
    forn(aff, 0, t) {
        cout<<"Case #"<<aff+1<<": ";
        ll n,k;
        cin>>n>>k;
        ll c1 = 1;
        ll c2 = 0;
        while(k>0) {
            ll nn = (n-1)/2;
            ll nc1 = 0;
            ll nc2 = 0;
            ll mn = n/2;
            ll mx = n-mn;
            if(k <= c2) {
                cout<<mx<<' '<<mn<<endl;
                break;
            }
            else {
                k-=c2;
                if(mn == nn) nc1+=c2;
                else nc2+=c2;
                nc2+=c2;
            }
            mn = (n-1)/2;
            mx = n-1 - mn;
            if(k <= c1) {
                cout<<mx<<' '<<mn<<endl;
                break;
            }
            else {
                k-=c1;
                if(mx == nn) nc1+=c1;
                else nc2+=c1;
                nc1+=c1;
            }
            n = nn;
            c1 = nc1;
            c2 = nc2;
        }
    }
    
    
}


