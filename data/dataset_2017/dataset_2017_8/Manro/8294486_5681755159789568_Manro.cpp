#include <bits/stdc++.h>
#define ff first
#define ss second
#define ALL(x) (x).begin(), (x).end()
#define D(x) cout << ">> " << #x << " = >" << x << "<" << endl
#define FOR(i,a,b) for ( int i = (a); i < (b); ++i )
#define FORD(i,a,b) for ( int i = (a); i >= (b); --i )
#define PB push_back
#define R1(a) scanf( "%d", &a )
#define R2(a,b) scanf( "%d%d", &a, &b )
#define R3(a,b,c) scanf( "%d%d%d", &a, &b, &c )
#define P( cond ) \
  do \
    { \
    if ( !( cond ) ) { \
      puts( "Nespravny vstup." ); \
      return 1; \
    } \
    } while(0)
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> Matrix;

const int INF = 1e9 + 7;
const double PI = acos(-1);
const double EPS = 1e-9;

const int N = 1e2+5;

ii cities[N];
double dist[N][N];

int main( )
{
	int t, n, e, s, d, u, v, q;
	cin >> t;

	FOR(caseNr,1,t+1) {
		cout << "Case #" << caseNr << ":";
		cin >> n >> q;
		FOR(i,0,n) {
			cin >> cities[i].ff >> cities[i].ss;
		}
		FOR(i,0,n) {
			FOR(j, 0, n) {
				cin >> dist[i][j];
				if ( dist[i][j] < 0 )
					dist[i][j] = 1e18;
			}
		}
		FOR(i,0,n)
			dist[i][i] = 0;
		FOR(k,0,n)
			FOR(i,0,n)
				FOR(j,0,n)
					dist[i][j] = min( dist[i][j], dist[i][k] + dist[k][j] );
		double time[N] = { 0 };
		FOR(i,1,N)
			time[i] = 1e18;
		FOR(u,0,n) {
			FOR(v,u+1,n) {
				if ( dist[u][v] <= cities[u].ff ) {
					time[v] = min( time[v], time[u] + dist[u][v] / cities[u].ss );
				}
			}
		}
		FOR(i,0,q) {
			cin >> u >> v;
			printf(" %.8f", time[v-1]);
		}
		printf("\n");
	}
	return 0;
}

