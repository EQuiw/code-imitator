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
typedef long double ld;
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
    scanf("%d", &t);
    forn(iad,0,t) {
        printf("Case #%d: ", iad+1);
        int n;
        int r,o,y,g,b,v;
        string ans;
        cin>>n>>r>>o>>y>>g>>b>>v;
        if(r+y == 0) {
            if(g>0 || v >0 || b!=o) {
                cout<<"IMPOSSIBLE\n";
                continue;
            }
            else {
                forn(i,0,b) ans+="BO";
                cout<<ans<<endl;
                continue;
            }
        }
        if(r+b == 0) {
            if(g>0 || o >0 || y!=v) {
                cout<<"IMPOSSIBLE\n";
                continue;
            }
            else {
                forn(i,0,y) ans+="YV";
                cout<<ans<<endl;
                continue;
            }
        }
        if(b+y == 0) {
            if(o>0 || v >0 || r!=g) {
                cout<<"IMPOSSIBLE\n";
                continue;
            }
            else {
                forn(i,0,g) ans+="RG";
                cout<<ans<<endl;
                continue;
            }
        }
        r-=g;
        y-=v;
        b-=o;
        if(r<0 || y<0 || b<0) {
            cout<<"IMPOSSIBLE\n";
            continue;
        }
        if(r==0 && g>0) {
            cout<<"IMPOSSIBLE\n";
            continue;
        }
        if(y==0 && v>0) {
            cout<<"IMPOSSIBLE\n";
            continue;
        }
        if(b==0 && o>0) {
            cout<<"IMPOSSIBLE\n";
            continue;
        }
        if(r+y<b || r+b<y || b+y<r) {
            cout<<"IMPOSSIBLE\n";
            continue;
        }
        int cnt = r+y+b;
        ans = string(cnt, '.');
        int cur = 0;
        if(2*r==cnt) {
            forn(i,0,r) {
                ans[2*i] = 'R';
            }
            forn(i,0,r) {
                if(y>0){
                    ans[2*i+1] ='Y';
                    y--;
                }
                else ans[2*i+1] = 'B';
            }
        }
        else if(2*b==cnt) {
            forn(i,0,b) {
                ans[2*i] = 'B';
            }
            forn(i,0,b) {
                if(y>0){
                    ans[2*i+1] ='Y';
                    y--;
                }
                else ans[2*i+1] = 'R';
            }
        }
        else if(2*y==cnt) {
            forn(i,0,y) {
                ans[2*i] = 'Y';
            }
            forn(i,0,y) {
                if(r>0){
                    ans[2*i+1] ='R';
                    r--;
                }
                else ans[2*i+1] = 'B';
            }
        }
        else {
            forn(i,0,cnt) {
                if(r>0) {
                    ans[cur] = 'R';
                    r--;
                }
                else if(y>0) {
                    ans[cur] = 'Y';
                    y--;
                }
                else if(b>0) {
                    ans[cur] = 'B';
                    b--;
                }
                cur+=2;
                if(cur>=cnt) cur = 1;
            }
        }
        if(g>0) {
            int k = 0;
            while(ans[k]!='R') k++;
            string bef = ans.substr(0,k);
            string aft = ans.substr(k);
            forn(i,0,g) bef+="RG";
            ans = bef+aft;
        }
        if(v>0) {
            int k = 0;
            while(ans[k]!='Y') k++;
            string bef = ans.substr(0,k);
            string aft = ans.substr(k);
            forn(i,0,v) bef+="YV";
            ans = bef+aft;
        }
        if(o>0) {
            int k = 0;
            while(ans[k]!='B') k++;
            string bef = ans.substr(0,k);
            string aft = ans.substr(k);
            forn(i,0,o) bef+="BO";
            ans = bef+aft;
        }
        cout<<ans<<endl;
    }
}


