#include <bits/stdc++.h>
#define ff first
#define ss second
#define ALL(x) (x).begin(), (x).end()
#define D(x) //cout << ">> " << #x << " = >" << x << "<" << endl
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

const int N = 1e2;

ll needed[N];
ll got[N][N];
bool available[N][N];
bool ispackage[N][N];
int n, p;

bool is_package( int p1, int p2 ) {
	D(2*needed[0]*1.1);
	D(2*needed[1]*1.1);
	D(got[0][p1]);
	D(got[1][p2]);
	FOR(i,1/*max( int(needed[0] * 0.9 / got[0][p1]), int(needed[1] * 0.9 / got[1][p2]) )*/,1e6+1) {
		if ( ( i * needed[0] * 0.9 <= got[0][p1] && i * needed[0] * 1.1 >= got[0][p1] ) &&
			( i * needed[1] * 0.9 <= got[1][p2] && i * needed[1] * 1.1 >= got[1][p2] ) ) {
			D("true");
			return true;
		}
		//if ( i * needed[0] * 0.9 > got[0][p1] || i * needed[1] * 0.9 > got[1][p2] )
		//	break;
	}
	return false;
}

int solve( int package ) {
	FOR(i,0,p)
		FOR(j,0,p)
			ispackage[i][j] = is_package(i,j);
	vi r;
	FOR(i,0,p)
		r.PB(i);
	int best = 0;
	do {
		int res = 0;
		FOR(i,0,p)
			if ( ispackage[i][r[i]])
				++res;
		best = max( best, res );
	} while ( next_permutation(r.begin(),r.end()));
	return best;
}

int main( )
{
	int t;
	cin >> t;

	FOR(caseNr,1,t+1) {
		cin >> n >> p;
		D(n);
		D(p);
		FOR(i,0,n)
			cin >> needed[i];
		FOR(i,0,n) {
			FOR(j, 0, p) {
				cin >> got[i][j];
				available[i][j] = 1;
			}
		}
		if ( n == 1 ) {
			needed[1] = 0;
			memset(got[1],0,sizeof(got[1]));
			FOR(i,0,p)
				available[1][i] = 1;
		}
		cout << "Case #" << caseNr << ": " << solve( 0 ) << endl;
	}
	return 0;
}
