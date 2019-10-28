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
#define N 30
lld r,c;
char a[N][N];
void go(lld x,lld y)
{
	char c=a[x][y];
	lld l=1,r=1;
	while(1)
	{
		if(a[x][y-l]!='?') break;
		a[x][y-l]=c;
		l++;
	}
	while(1)
	{
		if(a[x][y+r]!='?') break;
		a[x][y+r]=c;
		r++;
	}
}
int main()
{
	freopen("123.in","r",stdin);
	freopen("1234.out","w",stdout);
	lld t;
	cin>>t;
	rep(tt,1,t+1)
	{
		rep(i,0,N) rep(j,0,N) a[i][j]='-';
		cin>>r>>c;
		rep(i,1,r+1) rep(j,1,c+1) cin>>a[i][j];
		rep(i,1,r+1) rep(j,1,c+1) if(a[i][j]>='A' and a[i][j]<='Z') 
			go(i,j);
		int ind=-1,flag=0;
		rep(i,1,r+1) 
		{
			rep(j,1,c+1) if(a[i][j]!='?') {
				ind=i;
				flag=1;
				break;
			}
			if(flag==1) break;
		}
		rep(i,1,ind) 
		{
			flag=0;
			rep(j,1,c+1) if(a[i][j]!='?') {
				flag=1;
				break;
			}
			if(flag==0)
				rep(j,1,c+1) a[i][j]=a[ind][j];
		}
		rep(i,ind,r+1)
		{
			flag=0;
			rep(j,1,c+1) if(a[i][j]!='?') {
				flag=1;
				break;
			}
			if(flag==0) rep(j,1,c+1) a[i][j]=a[i-1][j];
		}
		cout<<"Case #"<<tt<<":\n";
		rep(i,1,r+1) 
		{
			rep(j,1,c+1) cout<<a[i][j];
			br;
		}
	}
	return 0;
}