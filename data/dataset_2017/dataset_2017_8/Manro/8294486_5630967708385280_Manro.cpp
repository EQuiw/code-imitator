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

const int N = 1e6+5;

int main( )
{
	int t, d, n, k, s;
	cin >> t;

	FOR(caseNr,1,t+1) {
		double maxSpeed;
		cin >> d >> n;
		FOR(i,0,n) {
			cin >> k >> s;
			double speed = d / (double(d-k) / s);
			if ( !i || speed < maxSpeed )
				maxSpeed = speed;
		}
		printf("Case #%d: %.8f\n", caseNr, maxSpeed);
//		cout << "Case #" << caseNr << ": " << setprecimaxSpeed << endl;
	}
	return 0;
}
