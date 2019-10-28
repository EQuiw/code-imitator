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
        ll n;
        cin>>n;
        ll was = n;
        vi a;
        while(n>0) {
            a.pb(n%10);
            n/=10;
        }
        reverse(all(a));
        int l = a.size();
        int d = -1;
        forn(i,0,l-1) {
            if(a[i] > a[i+1]) {
                d=i;
                break;
            }
        }
        if(d==-1) {
            cout<<was<<endl;
            continue;
        }
        else {
            forn(i,d+1,l) a[i] = 9;
            a[d]--;
            while(d>0 && a[d]<a[d-1]) {
                a[d] = 9;
                d--;
                a[d]--;
            }
        }
        int s =0;
        while(a[s] == 0) s++;
        forn(i,s,l) cout<<a[i];
        cout<<endl;
    }
    
    
}


