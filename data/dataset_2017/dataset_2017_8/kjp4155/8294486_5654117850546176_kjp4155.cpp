#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#include <assert.h>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <iostream>
#include <functional>
#include <vector>
#include <stack>
#include <deque>

using namespace std;
typedef long long ll;
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
#define INF 1987654321

int N,M,T,K,tc;

void solve(){
	geti(N);
	int R,O,Y,G,B,V;
	geti(R,O,Y,G); geti(B,V);
	if( R + B + Y == 1 ){
		if( R == 1 ) printf("R");
		else if( B == 1 ) printf("B");
		else if( Y == 1 ) printf("Y");
		printf("\n"); return;
	}
	if( R + B < Y || B + Y < R || Y + R < B ){
		printf("IMPOSSIBLE\n"); return;
	}
	char a,b,c; a = 'R'; b = 'B'; c = 'Y';
	int ac=R,bc=B,cc=Y;
	if( ac < bc ){
		swap(ac,bc); swap(a,b);
	}
	if( ac < cc ) {
		swap(ac,cc); swap(a,c);
	}
	if( bc < cc ){
		swap(bc,cc); swap(b,c);
	}

	char last = '1';
	while(ac>0){
		if( bc > cc ){
			printf("%c%c",a,b); bc--; ac--;
			last = b;
		}
		else{
			printf("%c%c",a,c); cc--; ac--;
			last = c;
		}
	}
	if( last == c ){
		while( bc > 0 && cc > 0){
			printf("%c%c",b,c); bc--; cc--;
		}
	}
	else if( last == b ){
		while( cc > 0  && bc > 0){
			printf("%c%c",c,b); cc--; bc--;
		}
	}
	if( bc > 0 ) printf("%c",b);
	if( cc > 0 ) printf("%c",c);

	printf("\n");
}

int main() {
	freopen("output.txt","w",stdout);
	scanf("%d\n",&tc);
	for(int tt=1;tt<=tc;tt++){
		printf("Case #%d: ",tt);
		solve();
	}
}