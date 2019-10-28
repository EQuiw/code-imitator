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
#define input freopen("input1.txt","r",stdin);
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
 
int req[110],lb[110],ub[110];
int q[110][110];
int main()
{
	#ifndef ONLINE_JUDGE
        input;
        output;
    #endif
	int n,i,j,k,l,m,t,s=0,d,r,ans,p;
	S(t);
		int c=1;
	while(t--){
		Reset(req,0);
		Reset(lb,0);
		Reset(ub,0);
		Reset(q,0);
 		S(n);S(p);
 		for(i=0;i<n;i++) {
 			S(req[i]);
 		}
 		for(i=0;i<n;i++) {
 			for(j=0;j<p;j++) {
 				S(q[i][j]);
 			}
 		}
 		for(i=0;i<n;i++) {
 			sort(q[i],q[i]+p);
 		}
 		for(i=0;i<n;i++) {
 			double nt=(9*req[i])/10.0;
 			lb[i]=(int)nt;
 			if(lb[i]<nt) lb[i]++;
 			 ub[i]=(11*req[i])/10;
 		}
 		int ns;
 		ans = 0;
 		bool vis[52][52];
 		Reset(vis,0);
 		// debugarr(q[1],2);
 		for(i=0;i<n;i++) {
 			for(j=0;j<p;j++) {
 				if(q[i][j]<lb[i])
 continue;
  				ns = q[i][j]/lb[i];
 				int mx = q[i][j]/ub[i];
 				if(mx*ub[i]<q[i][j]) {
 					mx++;
 				}
 				swap(mx,ns);
 				while(ns<=mx) {
 					bool f=1;
 					// cout<<ns<<' '<<ns*lb[i]<<' '<<q[i][j]<<' '<<ns*ub[i]<<endl;;
 					vector< pair<int,int> > v;
 					v.clear();
 					for(int m=i+1;m<n;m++) {
 						f=0;
 						for(int o=0;o<p;o++) {
 							// cout<<m<<' '<<o<<' '<<ns<<' '<<ns*lb[m]<<' '<<q[m][o]<<' '<<ns*ub[m]<<' '<<vis[m][o]<<endl;;
 							if(!vis[m][o] && ns*lb[m]<=q[m][o] && ns*ub[m]>=q[m][o]) {vis[m][o]=true;v.push_back(make_pair(m,o));f=1;break;}
 						}
 						// cout<<f<<endl;
 						if(f==0) break;
 					}
 					if(f==0) {
 						for(int o=0;o<v.size();o++) {
 							vis[v[o].first][v[o].second] = false;
 						}
 					} else {
 						ans++;

 						break;
 					}
 					ns++;
 				}
 			}
 			break;
 		}
 		printf("Case #%d: %d\n",c++,ans);
 	}
	return (0);
} 
