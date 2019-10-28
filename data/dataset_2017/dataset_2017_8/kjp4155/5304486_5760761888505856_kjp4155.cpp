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
char p[40][40];

void solve(){
	geti(N,M);
	repp(i,N) scanf("%s",p[i]+1);

	repp(i,N){
		for(int j=2;j<=M;j++){

			if( p[i][j] == '?' ){
				if( p[i][j-1] != '?' ){
					p[i][j] = p[i][j-1];
				}
			}
		}
	}

	repp(i,N){
		for(int j=M-1;j>=1;j--){
			if( p[i][j] == '?' ){
				if( p[i][j+1] != '?' ){
					p[i][j] = p[i][j+1];
				}
			}
		}
	}

	for(int j=1;j<=M;j++){
		for(int i=2;i<=N;i++){
			if( p[i][j] == '?' ){
				if( p[i-1][j] != '?' ){
					p[i][j] = p[i-1][j];
				}
			}
		}
	}

	for(int j=1;j<=M;j++){
		for(int i=N-1;i>=1;i--){
			if( p[i][j] == '?' ){
				if( p[i+1][j] != '?' ){
					p[i][j] = p[i+1][j];
				}
			}
		}
	}
	printf("\n");
	repp(i,N) printf("%s\n",p[i]+1);

}

int main(void)
{
	freopen("output.txt","w",stdout);
	geti(tc);
	repp(t,tc){
		printf("Case #%d: ",t);
		solve();
	}
}


