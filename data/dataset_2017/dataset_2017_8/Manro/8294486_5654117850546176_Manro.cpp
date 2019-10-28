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

const int N = 1e2;

enum { R, O, Y, G, B, V };
vector<char> res;

bool solve( int r, int y, int b ) {
	int mx = max( r, max( y, b ) );
//	D(mx);
	if ( !r && !y && !b ) {
		return res.back( ) != res[0];
	}
	if ( r && mx == r && res.back( ) != 'R' ) {
		res.PB('R');
		if ( solve( r - 1, y, b ) )
			return true;
		res.pop_back();
	}
	if ( y && mx == y && res.back( ) != 'Y' ) {
		res.PB('Y');
		if ( solve( r, y - 1, b ) )
			return true;
		res.pop_back();
	}
	if ( b && mx == b && res.back( ) != 'B' ) {
		res.PB('B');
		if ( solve( r, y, b - 1 ) )
			return true;
		res.pop_back();
	}
	if ( r && mx != r && res.back( ) != 'R' ) {
		res.PB('R');
		if ( solve( r - 1, y, b ) )
			return true;
		res.pop_back();
	}
	if ( y && mx != y && res.back( ) != 'Y' ) {
		res.PB('Y');
		if ( solve( r, y - 1, b ) )
			return true;
		res.pop_back();
	}
	if ( b && mx != b && res.back( ) != 'B' ) {
		res.PB('B');
		if ( solve( r, y, b - 1 ) )
			return true;
		res.pop_back();
	}
	return false;
}

int main( )
{
	int t, n, r, o, y, g, b, v;
	cin >> t;

	FOR(caseNr,1,t+1) {
		cin >> n >> r >> o >> y >> g >> b >> v;
		cout << "Case #" << caseNr << ": ";
		int mx = max( r, max( y, b ) );
		if ( mx > r + y + b - mx ) {
			cout << "IMPOSSIBLE" << endl;
			continue;
		}
		res.clear();
		if ( mx == r ) {
			res.PB('R');
			--r;
		} else if ( mx == y ) {
			res.PB('Y');
			--y;
		}
		else if ( mx == b ) {
			res.PB('B');
			--b;
		}
		if ( !solve( r, y, b ) ) {
			cout << "IMPOSSIBLE" << endl;
			continue;
		} else {
			for ( char c : res )
				cout << c;
			cout << endl;
		}
	}
	return 0;
}
