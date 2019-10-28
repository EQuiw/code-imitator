#include<bits/stdc++.h>
#define rep(i,start,lim) for(lld i=start;i<lim;i++)
#define repd(i,start,lim) for(lld i=start;i>=lim;i--)
#define scan(x) scanf("%lld",&x)
#define print(x) printf("%lld ",x)
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define br printf("\n")
#define YES printf("YES\n")
#define NO printf("NO\n")
#define all(c) (c).begin(),(c).end()
using namespace std;
#define INF         1011111111
#define LLINF       1000111000111000111LL
#define EPS         (double)1e-10
#define MOD         1000000007
#define PI          3.14159265358979323
using namespace std;
typedef long double ldb;
typedef long long lld;
lld powm(lld base,lld exp,lld mod=MOD) {lld ans=1;while(exp){if(exp&1) ans=(ans*base)%mod;exp>>=1,base=(base*base)%mod;}return ans;}
typedef vector<lld> vlld;
typedef pair<lld,lld> plld;
typedef map<lld,lld> mlld;
typedef set<lld> slld;
#define N 100005
lld k[N],s[N];
int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	lld t,n,d;
	ldb ans;
	cin>>t;
	rep(tt,1,t+1)
	{
		cin>>d>>n,ans=LLINF;
		rep(i,1,n+1) cin>>k[i]>>s[i],ans=min(ans,((ldb)(d*s[i])/(d-k[i])));
		cout<<"Case #"<<tt<<": "<<fixed<<setprecision(7)<<ans<<endl;
	}
	return 0;
}