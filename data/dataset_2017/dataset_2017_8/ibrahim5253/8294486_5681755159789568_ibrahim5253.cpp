#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<cmath>
#include<stack>
#include<climits>
#include<map>
#include<set>
#include<utility>
#include<iterator>
#include<cstring>
#include<cstdio>
#include<unordered_map>
#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define umap unordered_map
#define ff first
#define ss second
//#define scd static_cast<double>
using namespace std;
using ll=long long;
using ull=unsigned long long;
using pii=pair<int, int>;
using pll=pair<ll,ll>;
using vi=vector<int>;
using vll=vector<ll>;
using pill=pair<int,ll>;
using vvi=vector<vi>;

ll gcd(ll a, ll b)
{	
	ll t;
	while((t=a%b)!=0) {
		a=b;
		b=t;
	}
	return b;
}

ll fast_exp(ll base, ll n, ll m)
{
	if(n==0)	return 1;
	ll t=fast_exp(base,n/2,m);
	if(n%2==0)	return (t*t)%m;
	else	return (((t*t)%m)*base)%m;
}

bool is_set(int i, ll mask)
{
	return (mask>>i)&1;
}

int count_bits(ll mask)
{
	int ans=0;
	for(int i=0;i<64;++i)
		if (is_set(i,mask)) ++ans;
	return ans;	
}

int first_bit(ll mask)
{	
	int i=0;
	while(i<64) 
		if(is_set(i++, mask)) return i-1;
	return -1;
}

int main()
{
	ios::sync_with_stdio(false);
    int t;cin>>t;
    for (int i=1;i<=t;++i) {
        int n, q;cin>>n>>q;
        ll e[n], s[n];
        for (int i=0;i<n;++i) cin>>e[i]>>s[i];
        ll d[n][n];
        for (int i=0;i<n;++i)
            for (int j=0;j<n;++j) cin>>d[i][j];
        {
            int u, v;cin>>u>>v;
            --u,--v;
            double dp[n];
            dp[0]=0;
            for (int i=1;i<n;++i) {
                dp[i]=1e12;
                ll dist=0;
                for (int j=i-1; j>=0; --j) {
                    dist+=d[j][j+1];
                    if (e[j]>dist) dp[i]=min(dp[i],dp[j]+dist/static_cast<double>(s[j]));
                }
            }
            printf("Case #%d: %.10f\n",i,dp[v]);
        }
    }
	return 0;
}
