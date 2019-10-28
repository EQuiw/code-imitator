#include <algorithm>
#include <cfloat>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
#define mp make_pair
#define forf(i, n) for (int i = 0; i < n; i++)
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<double> vd;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef set<int> si;
typedef vector<si> vsi;
using namespace std;

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
        int d, n;
        cin >> d >> n;
        vi k(n), s(n);
        long double ans = d;
        forf(i, n) {
            cin >> k[i] >> s[i];
            //double t = (double) (d - k[i]) / s[i];
            //ans = min(ans, (double) d / t);
            ans = min(ans, (long double) d * s[i] / (d - k[i]));
        }
		cout << "Case #" << t << ": ";
        cout << fixed << setprecision(8) << ans << '\n';
	}
	return 0;
}
