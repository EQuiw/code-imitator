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
pair<lld,char> a[3];
int main()
{
	freopen("5.in","r",stdin);
	freopen("6.out","w",stdout);
	lld t,n,r,o,y,g,b,v;
	cin>>t;
	rep(tt,1,t+1)
	{
		cin>>n>>r>>o>>y>>g>>b>>v;
		lld curr=0,sz=0,flag=0;
		string ans="";
		a[0]={r,'R'};
		a[1]={y,'Y'};
		a[2]={b,'B'};
		sort(a,a+3),reverse(a,a+3);
		while(1)
		{
			//cout<<ans<<" "<<curr<<" "<<sz<<" "<<ans[sz]<<endl;
			if(a[curr].f)
			{
				if(!sz or ans[sz-1]!=a[curr].s) 
					ans+=a[curr].s,sz++,a[curr].f--,curr=(curr+1)%3;
				else {
					flag=1;
					break;
				}
			}
			else curr=(curr+1)%3;
			if(a[0].f==0 and a[1].f==0 and a[2].f==0) break;
		}
		cout<<"Case #"<<tt<<": ";
		if(flag==0) cout<<ans<<endl;
		else cout<<"IMPOSSIBLE\n";
	}
	return 0;
}