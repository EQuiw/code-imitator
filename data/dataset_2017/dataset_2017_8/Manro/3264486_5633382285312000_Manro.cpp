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

const int N = 1e6+5;

bool isTidy(ll n) {
	stringstream ss;
	ss << n;
	string num = ss.str();
	return is_sorted(num.begin(),num.end());
}

int main( )
{
	int t,k;
	ll n;
	string s;
	cin >> t;

	FOR(caseNr,1,t+1) {
		cout << "Case #" << caseNr << ": ";
		cin >> n;
		int res = 1;
		FOR(i,1,n+1)
			if ( isTidy( i ))
				res = i;
		cout << res << endl;
	}
	return 0;
}
