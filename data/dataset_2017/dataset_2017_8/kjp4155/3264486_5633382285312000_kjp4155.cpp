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

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> Pi;

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

#define GET_MACRO(_1,_2,_3,_4,NAME,...) NAME
#define geti(...) GET_MACRO(__VA_ARGS__, geti4, geti3, geti2, geti1) (__VA_ARGS__)

#define INF 987654321
#define IINF 987654321987654321

int N,M,T,K,tc;

int p[1050];
void solve(){
	string s; cin >> s;
	int len = s.size();
	int x = -1;
	for(int i=0;i<len;i++){
		p[i+1] = s[i]-'0';
	}
	for(int i=1;i<=len-1;i++){
		if( p[i] > p[i+1] ){
			x = i; break;
		}
	}
	
	if( x == -1 ){
		cout << s << endl; return;
	}
	int y = -1;
	for(int i=x;i>=1;i--){
		if( p[i] > p[i-1] ){
			y = i; break;
		}
	}

	if( y == -1 ){
		rep(i,len-1) printf("9");
		printf("\n"); return;
	}
	p[y]--;


	bool start = false;
	for(int i=0;i<=y;i++){
		if( p[i] != 0 ) start = true;
		if( start ) printf("%d",p[i]);
	}
	for(int i=y+1;i<=len;i++) printf("9");
	printf("\n");

}

bool ascending(int x){
	int q[100];
	int pos = 0;

	while( x > 0 ){
		q[pos] = x%10; x/=10; pos++;
	}
	for(int i=0;i<pos-1;i++){
		if( q[i] < q[i+1] ){	
			return false;
		}
	}

	return true;
}

void solve2(){
	int x; cin >> x; 
	for(int i=x;i>=0;i--){
		if( ascending(i) ){
			cout << i << endl ;
			return;
		}
	}

}


int main(void)
{
	freopen("output1.txt","w",stdout);
	geti(tc);
	for(int tcx=1;tcx<=tc;tcx++){
		printf("Case #%d: ",tcx);
		solve2(); 
		//solve(); 
	}
}
