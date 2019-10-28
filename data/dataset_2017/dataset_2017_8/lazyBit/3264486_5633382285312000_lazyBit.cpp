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

bool containszero(int l) {
	int i=0;
	while(str[i]=='0') {
		i++;
	}
	while(i<l) {
		if(str[i]=='0') return true;
		i++;
	}
	return false;
}
int main()
{
	// #ifndef ONLINE_JUDGE
 //        input;
 //        output;
 //    #endif
	int n,i,j,k,l,m,t,s=0,d;
	S(t);
		int c=1;
	while(t--){
 		cin>>str;
 		bool p=0;
 		l= strlen(str);
 		 if(!containszero(l)) {
 			for(i=l-1;i>0;i--) {
 					if(str[i]<str[i-1]) {
 					for(j=i;j<l;j++) str[j]='9'; 
 					str[i-1]=(char)(str[i-1]-1);
 					}
 				}
 		}
        while(containszero(l)) {
 		for(i=0;i<l;i++) {
 			if(str[i]=='0') {
 				for(j=i;j<l;j++) str[j]='9';
 				str[i-1]=(char)(str[i-1]-1);
 				break;
 			}
 		}
 		if(!containszero(l)) {
 			for(i=l-1;i>0;i--) {
 					if(str[i]<str[i-1]) {
 					for(j=i;j<l;j++) str[j]='9'; 
 					str[i-1]=(char)(str[i-1]-1);
 					}
 				}
 			}
 		}
 		printf("Case #%d: ",c++);
 		i=0;
 		while(str[i]=='0') {
 			i++;
 			continue;
 		}
 		while(i<l) {
 			cout<<str[i++];
 		}
 		printf("\n");
 	}
	return (0);
} 
