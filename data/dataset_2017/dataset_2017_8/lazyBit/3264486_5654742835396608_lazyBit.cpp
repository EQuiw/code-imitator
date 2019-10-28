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
 
#define S(x)            scanf("%d",&x);
#define input freopen("input.txt","r",stdin);
#define output freopen("output_small.txt","w",stdout);
#define deb(i,a,n) for(i=0;i<n;i++){cout<<a[i]<<" ";}
#define db(x,y)          printf("%d %d\n",x,y);
#define debug(args...)	{dbg,args; cerr<<endl;}
#define dline			cerr<<endl	
#define INF				(int)1e9
#define LINF			(long long)1e18
#define EPS				1e-9
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
 
char str[50];

long long pow2(int a, long long int b)
 		{
 			long long x=1,y=a; 
 			while(b > 0)
 			{
 				if(b%2 == 1)
 				{
 					x=(x*y);
 				}
 				y = (y*y);
 				b /= 2;
 			}
 			return x;
 		}
LL dist[2];
int main()
{
	// #ifndef ONLINE_JUDGE
 //        input;
 //        output;
 //    #endif
	int i,j,l,m,t,s=0,d;
	LL n,k,x,x1,level,used,prevLevel,rem;
	S(t);
	int c=1;
	while(t--){
 		cin>>n;
 		cin>>k;
 		x = n;
 		x1 = n;
 		level = log2(k);
 		dist[0]=1;
 		dist[1]=0;
 		LL tempx,tempx1;
 		LL tempdist[2];
 		for(i=1;i<=level;i++) {
 			tempdist[0]=0;
 			tempdist[1]=0;
 			if(x&1) {
 				tempx = x/2;
 				tempx1 = tempx;
 				tempdist[0]=2*dist[0];
 			} else {
 				tempx = (x-1)/2;
 				tempx1 = tempx+1;
 				tempdist[0]=dist[0];
 				tempdist[1]=dist[0];
 			}

            if(dist[1]>0) {
 				if(!(x1&1)) {
 					tempx = (x1-1)/2;
 					tempx1 = x1/2;
 					tempdist[0]+=dist[1];
 					tempdist[1]+=dist[1];
 				} else {
 					tempx1 = x1/2;
 					tempdist[1]+=2*dist[1];
 				}
 			}
 			x = tempx;
 			x1 = tempx1;
 			dist[0] = tempdist[0];
 			dist[1] = tempdist[1];
 		}
 		prevLevel = pow2(2,level) - 1;
 		rem = k - prevLevel;
 		// cout<<x<<' '<<x1<<' '<<dist[0]<<' '<<dist[1]<<endl;
 		if(rem > dist[1]) {
 			used = x;
 		} else {
 			used = x1;
 		}
 		// debug(prevLevel,rem,x,x1,used);
 		// cout<<used<<endl;
 		if(used&1) {
 			cout<<"Case #"<<c++<<": "<<used/2<<" "<<used/2<<endl;
 		} else {
 			cout<<"Case #"<<c++<<": "<<used/2<<" "<<(used-1)/2<<endl;
 		}
 	}
	return (0);
} 
