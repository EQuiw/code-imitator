#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lp(i,a,n) for(int i=(a);i<=(int)(n);++i)
#define lpd(i,a,n) for(int i=(a);i>=(int)(n);--i)
#define mem(a,b) memset(a,b,sizeof a)
#define all(v) v.begin(),v.end()
#define println(a) cout <<(a) <<endl
#define sz(x) ((int)(x).size())
#define readi(x) scanf("%d",&x)
#define read2i(x,y) scanf("%d%d",&x,&y)
#define read3i(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define readll(x) scanf("%I64d",&x)
#define mod 1000000007
#define eps 1e-6
#define infi 1000000000
#define infll 1000000000000000000ll
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vll;
typedef set<int> si;
typedef map<int,int> mii;

const int N = 102;
int t,n,q,dist[N],speed[N],u,v;
vector<vector<pii>> g(N);
bool vis[N];
double dp[N];

double solve(int i){
    if(i == v) return 0;
    if(!sz(g[i])) return infll;
    if(vis[i]) return dp[i];
    vis[i] = true;

    dp[i] = infll;
    double totalDist = g[i].back().s;
    int j = g[i].back().f;
    while(totalDist <= dist[i]){
        dp[i] = min(dp[i], totalDist / speed[i] + solve(j));
        if(j == v) break;
        if(!sz(g[j])) return dp[i];
        totalDist += g[j].back().s;
        j = g[j].back().f;
    }
    return dp[i];
}

int main(){
    freopen("C-small-attempt0.in","r",stdin);
    freopen("output.txt","w",stdout);

    readi(t);
    lp(test,1,t){
        read2i(n,q);
        lp(i,1,n) read2i(dist[i],speed[i]);
        lp(i,1,n) lp(j,1,n){
            int a; readi(a);
            if(a != -1) g[i].pb(mp(j,a));
        }
        while(q--){
            read2i(u,v);
            mem(vis,0);
            printf("Case #%d: %.6f\n",test,solve(u));
        }

        g.clear(), g.resize(N);
    }
}

//freopen("input.txt","r",stdin);
//freopen("output.txt","w",stdout);
//ios::sync_with_stdio(0);cin.tie(0);
