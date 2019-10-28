#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <memory.h>
#include <math.h>
#include <assert.h>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <stack>
#include <unordered_map>
#include <deque> 
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> Pi;
typedef pair<ll,ll> Pll;

#define Fi first
#define Se second
#define pb(x) push_back(x)
#define sz(x) (int)x.size()
#define rep(i, n) for(int i=0;i<n;i++)
#define repp(i, n) for(int i=1;i<=n;i++)
#define all(x) x.begin(), x.end()

#define ABS(x) (((x) > 0 ) ? (x) : (-(x)))
#define MAX2(x, y) (((x) > (y)) ? (x) : (y))
#define MIN2(x, y) (((x) < (y)) ? (x) : (y))

#define MAX3(x, y, z) ( (x) > (y)  ? ( (x) > (z) ? (x) : (z)  ) : ( (y) > (z) ? (y) : (z) )  )
#define MIN3(x, y, z) ( (x) < (y)  ? ( (x) < (z) ? (x) : (z)  ) : ( (y) < (z) ? (y) : (z) )  )
#define MID3(val1,val2,val3) MAX2(MIN2(MAX2(val1,val2),val3),MIN2(val1,val2))

#define geti1(X) scanf("%d",&X)
#define geti2(X,Y) scanf("%d%d",&X,&Y)
#define geti3(X,Y,Z) scanf("%d%d%d",&X,&Y,&Z)
#define geti4(X,Y,Z,W) scanf("%d%d%d%d",&X,&Y,&Z,&W)

#define debug1(X) cout << X << endl;
#define debug2(X,Y) cout << X << " " << Y << endl;
#define debug3(X,Y,Z) cout << X << " " << Y << " " << Z << endl;
#define debug4(X,Y,Z,W) cout << X << " " << Y << " " << Z << " " << W << endl;

#define GET_MACRO(_1,_2,_3,_4,NAME,...) NAME

#define geti(...) GET_MACRO(__VA_ARGS__, geti4, geti3, geti2, geti1) (__VA_ARGS__)
#define debug(...) GET_MACRO(__VA_ARGS__, debug4, debug3, debug2, debug1) (__VA_ARGS__)



#define INF 987654321
#define IINF 987654321987654321

#define MAXV 200500
#define MAXM 1050

int N,M,K,tc;
ll r[150];
ll p[150][150]; 
set<Pll> cur[150]; Pll range[150][150];
struct event{
	ll n; ll x; ll y; ll t;
};

bool cmp(event e1, event e2){
	if( e1.n == e2.n ) return e1.t > e2.t;
	return e1.n < e2.n;
}
ll gcd(ll a, ll b){
	if( b == 0 ) return a;
	return gcd( b , a % b );
}
struct fraction{
	ll x,y;
	fraction(){
		x = 0; y = 1;
	}
	fraction(ll _x, ll _y){
		x = _x; y = _y;
		ll g = gcd(x,y);
		x = x/g; y = y/g;
	}

	ll ceil(){
		return (x+y-1)/y;
	}
	ll floor(){
		return x/y;
	}
	void print(){
		printf("%lld/%lld",x,y);
	}
	fraction operator * (fraction a ){
		fraction res = fraction( a.x * x , a.y * y );
		return res;
	}
};

void solve2(){
	rep(i,150)rep(j,150) range[i][j] = {-1,-1};
	rep(i,150) cur[i].clear();
	memset(p,0,sizeof p);
	memset(r,0,sizeof r); 
	geti(N,M);
	repp(i,N) scanf("%lld",r+i);
	repp(i,N){
		repp(j,M) scanf("%lld",&p[i][j]);
	}


	ll ans = 0;

	vector<int> v; for(int i=1;i<=M;i++) v.pb(i);

	repp(i,N){
		repp(j,M){
			fraction nl, nr; 
			nl = fraction(p[i][j],r[i]); nl = nl * fraction(10,11);
			nr = fraction(p[i][j],r[i]); nr = nr * fraction(10,9);
			
			ll nleft = nl.ceil();
			ll nright = nr.floor();
			if( nleft > nright ) continue;
			range[i][j] = {nleft,nright};
			event t1,t2;
			// 1 이면 들어오고 -1이면 나감
			//printf("[%lld,%lld]\n",nleft,nright);
		}
	}
		
	if( N == 1 ){
		repp(j,M){
			if( range[1][j].Fi != -1 && range[1][j].Se != -1 ) ans++;
		}
		printf("%lld\n",ans);
		return;
	}
	
	do{
		ll cnt = 0;
		for(int j=1;j<=M;j++){
			int jj = v[j-1];
			if( range[1][j].Fi == -1 || range[1][j].Se == -1 ) continue;
			if( range[2][jj].Fi == -1 || range[2][jj].Se == -1 ) continue;
			ll curl = range[1][j].Fi; ll curr = range[1][j].Se;
			curl = max(curl, range[2][jj].Fi); curr = min(curr, range[2][jj].Se);
			if( curl <= curr ) cnt++;
		}
		ans = max(cnt,ans);
	}while( next_permutation(all(v)) );

	printf("%lld\n",ans);	
}
void solve(){
	rep(i,150) cur[i].clear();
	memset(p,0,sizeof p);
	memset(r,0,sizeof r); 
	geti(N,M);
	repp(i,N) scanf("%lld",r+i);
	repp(i,N){
		repp(j,M) scanf("%lld",&p[i][j]);
	}


	ll ans = 0;
	vector<event> v;
	repp(i,N){
		repp(j,M){
			fraction nl, nr; 
			nl = fraction(p[i][j],r[i]); nl = nl * fraction(10,11);
			nr = fraction(p[i][j],r[i]); nr = nr * fraction(10,9);
			//nl = ((long double)1.0*p[i][j])/(1.0*r[i]); nl *= (10.0/11.0);
			//nr = ((long double)1.0*p[i][j])/(1.0*r[i]); nr *= (10.0/9.0);
			//cout << nl << " " << nr << endl;
			ll nleft = nl.ceil();
			ll nright = nr.floor();
			if( nleft > nright ) continue;
			//range[i][j] = {nleft,nright};
			event t1,t2;
			// 1 이면 들어오고 -1이면 나감
			t1.n = nleft; t1.y = i; t1.x = j; t1.t = 1;
			t2.n = nright; t2.y = i; t2.x = j; t2.t = -1;
			//printf("[%lld,%lld]\n",nleft,nright);
			v.push_back(t1); v.push_back(t2); 
		}
		//printf("\n");
	}
	sort(all(v),cmp);

	for(auto e : v){
		if( e.t == 1 ){
			cur[e.y].insert({e.n,e.x});
		}
		bool ok = true;
		repp(i,N){
			if( cur[i].size() == 0 ) ok = false;
		}
		if( ok ){
			ans++;
			repp(i,N){
				Pll die = *(cur[i].begin());
			//	printf("%lld ",p[i][die.Se]);
				cur[i].erase(die);
			}
			//printf("\n");
		}
		if( e.t == -1 ){
			if( cur[e.y].find({e.n,e.x}) != cur[e.y].end() ) cur[e.y].erase({e.n,e.x});
		}
	}

	
	printf("%lld\n",ans);
}

int main(void)
{
	freopen("output2.txt","w",stdout);
	geti(tc);
	repp(t,tc){
		printf("Case #%d: ",t);
		solve2();
	}
}


