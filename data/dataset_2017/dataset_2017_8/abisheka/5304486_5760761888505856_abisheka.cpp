#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<utility>
#include<set>
#include<stack>
#include<list>
#include<deque>
#include<bitset>
#include<iomanip>
#include<cstring>
#include<sstream>
#include<cstdio>
#include<cstdlib>
#include<climits>
#include<cmath>
#include<cctype>


#define pb push_back
#define mp make_pair
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define ren(i,a,b) for(int i=a;i>=b;i--)
#define ff first
#define ss second
#define pll pair<long long int,long long int>
#define pii pair<int,int>
#define vll vector<long long int>  
#define vii vector<int>
#define gi(n) scanf("%d",&n)
#define gll(n) scanf("%lld",&n)
#define gstr(n) scanf("%s",n)
#define gl(n) cin >> n
#define oi(n) printf("%d",n)
#define oll(n) printf("%lld",n)
#define ostr(n) printf("%s",n)
#define ol(n) cout << n
#define os cout<<" "
#define on cout<<"\n"
#define o2(a,b) cout<<a<<" "<<b
#define all(n) n.begin(),n.end()
#define present(s,x) (s.find(x) != s.end()) 
#define cpresent(s,x) (find(all(s),x) != s.end()) 
#define tr(container, it) for(__typeof(container.begin()) it = container.begin(); it != container.end(); it++) 
using namespace std;
 
typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<vector<ll> > mat;

int main()
{ios_base::sync_with_stdio(false);
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);
int t,t1=0;
gl(t);
while(t--)
{
	t1++;
	ol("Case #");ol(t1);ol(": ");
	int n,m;
	cin>>n>>m;
	string s[25];
	rep(i,0,n-1)cin>>s[i];
	int mnx[26],mxx[26],mny[26],mxy[26];
	rep(i,0,25)mxx[i]=mxy[i]=-1;
	rep(i,0,25)mnx[i]=mny[i]=1e9;
	rep(i,0,n-1)rep(j,0,m-1)
	{
		mnx[s[i][j]-'A']=min(mnx[s[i][j]-'A'],i);
		mxx[s[i][j]-'A']=max(mxx[s[i][j]-'A'],i);
		mny[s[i][j]-'A']=min(mny[s[i][j]-'A'],j);
		mxy[s[i][j]-'A']=max(mxy[s[i][j]-'A'],j);
	}
	
	rep(ii,0,25)
	{
		if(mxx[ii]==-1)continue;
		rep(i,mnx[ii],mxx[ii])rep(j,mny[ii],mxy[ii])s[i][j]=(char)('A'+ii);
	}
	
	rep(ii,0,25)
	{
		if(mxx[ii]==-1)continue;
		ren(j,mny[ii]-1,0)
		{
			int cool=0;
			rep(i,mnx[ii],mxx[ii])if(s[i][j]=='?')cool++;
			if(cool!=mxx[ii]-mnx[ii]+1)break;
			rep(i,mnx[ii],mxx[ii])s[i][j]=(char)('A'+ii);
			mny[ii]=j;
		}
		rep(j,mxy[ii]+1,m-1)
		{
			int cool=0;
			rep(i,mnx[ii],mxx[ii])if(s[i][j]=='?')cool++;
			if(cool!=mxx[ii]-mnx[ii]+1)break;
			rep(i,mnx[ii],mxx[ii])s[i][j]=(char)('A'+ii);
			mxy[ii]=j;
		}
	}
	
	rep(ii,0,25)
	{
		if(mxy[ii]==-1)continue;
		ren(i,mnx[ii]-1,0)
		{
			int cool=0;
			rep(j,mny[ii],mxy[ii])if(s[i][j]=='?')cool++;
			if(cool!=mxy[ii]-mny[ii]+1)break;
			rep(j,mny[ii],mxy[ii])s[i][j]=(char)('A'+ii);
		}
		rep(i,mxx[ii]+1,n-1)
		{
			int cool=0;
			rep(j,mny[ii],mxy[ii])if(s[i][j]=='?')cool++;
			if(cool!=mxy[ii]-mny[ii]+1)break;
			rep(j,mny[ii],mxy[ii])s[i][j]=(char)('A'+ii);
		}
	}
	on;
	rep(i,0,n-1)
	{
		rep(j,0,m-1)
		{
			ol(s[i][j]);
		}
		on;
	}	
}
return 0;
}
