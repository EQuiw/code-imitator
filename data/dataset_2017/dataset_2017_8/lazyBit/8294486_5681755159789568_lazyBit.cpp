#include <set>
#include <bitset>
#include <queue>
#include <deque>
#include <stack>
#include <sstream>
#include <iostream>
#include <iomanip>
 
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>
#include <string>
#include <cassert>
 
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
// #include <random>
 
using namespace std;
 
typedef vector <int> vi;
typedef vector <vi> vvi;
typedef pair <int, int> ii;
typedef vector <ii> vii;
typedef vector <string> vs;
 
typedef long long LL; //NOTES:int64
typedef unsigned long long ULL; //NOTES:uint64
typedef unsigned uint;
 
const double pi = acos(-1.0); //NOTES:pi
const double eps = 1e-11; //NOTES:eps
const int MAXI = 0x7fffffff;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};
const char colors[] = {'R','O','Y','G','B','V'};
const char dz[] = "SENW";
 
#define rep(i,n)        for (int i=0;i<n;i++)
#define loop(i,a,b)     for (int i=(a),_b=(b); i<_b; i++)
#define rloop(i,b,a)    for (int i=(b)-1,_a=(a); i>=_a; i--)
#define Reset(a,b)      memset((a),(b),sizeof(a))
 
#define endline         putchar('\n')
#define space           putchar(' ')
#define EXIT(x)         {cout << x;return 0;}
 
#define fi              first
#define se              second
#define pb              push_back
 
#define S(x)            scanf("%lld",&x);
#define input freopen("input.txt","r",stdin);
#define output freopen("output_small_1.txt","w",stdout);
#define deb(i,a,n) for(i=0;i<n;i++){cout<<a[i]<<" ";}
#define db(x,y)          printf("%d %d\n",x,y);
#define debug(args...)	{dbg,args; cerr<<endl;}
#define dline			cerr<<endl	
#define INF				(int)1e9
#define LINF			(long long)1e18
#define EPS				1e18
#define maX(a,b)		((a)>(b)?(a):(b))
#define miN(a,b)		((a)<(b)?(a):(b))
#define abS(x)			((x)<0?-(x):(x))
#define mod             1000000007
 
struct debugger
{
	template<typename T> debugger& operator , (const T& v)
	{	
		cerr<<v<<" ";	
		return *this;	
	}
} dbg;
 
void debugarr(int * arr,int n)
{
	cout<<"[";
	for(int i=0;i<n;i++)
		cout<<arr[i]<<" ";
	cout<<"]"<<endl;
}
 
double besttime[1010];
LL c[110],d[110],dist[110][110],a[110],b[110],dd[110];
long double best[110][110];
int main()
{
	#ifndef ONLINE_JUDGE
        input;
        // output;
    #endif
	long long n,k,l,m,t,s=0,p,q;
	int i,j;
	cin>>t;
	int ct=1;
	while(t--){
		S(n);S(q);
		for(i=0;i<n;i++) {
			S(c[i]);S(d[i]);
		}
		for(i=0;i<n;i++) {
			for(j=0;j<n;j++) {
				S(dist[i][j]);
			}
		}
		for(i=0;i<q;i++) {
			S(a[i]);S(b[i]);
		}
		dd[0]=0;
		for(i=1;i<n;i++) {
			dd[i]=dd[i-1]+dist[i-1][i];
		}
		besttime[0]=0.0;
		long double r;
		for(i=1;i<n;i++) {
			r = EPS;
			for(j=0;j<i;j++) {
				if(dd[i]-dd[j]<=c[j]) {
					best[i][j]=besttime[j] + ((dd[i]-dd[j])*1.0)/d[j];
				} else {
					best[i][j]=EPS;
				}
				r = min(r,best[i][j]);
			}
			besttime[i]=r;
		}
		// if(besttime[n-1]<0) {
		// 	cerr<<n<<' '<<q<<endl;
		// }
		printf("Case #%d: %0.6lf\n",ct++,besttime[n-1]);
 	}
	return (0);
} 
