#include <algorithm>
#include <climits>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
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

/*
bool min(long double a, long double b) {
    if (a < b) {
        return a;
    }
    return b;
}
*/

/*
struct city {
    int e, s, d;
    bool operator<(const city& other) const {
        return d < other.d;
    }
}
*/

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
        int n, q;
        cin >> n >> q;
        //vector<struct city> cities(n);
        vi e(n), s(n);
        vvi d(n, vi(n));
        vi u(q), v(q);
        forf(i, n) {
            cin >> e[i] >> s[i];
            /*
            int e, s;
            cin >> e >> s;
            struct city c;
            c.e = e;
            c.s = s;
            cities[i] = c;
            */
        }
        forf(i, n) {
            forf(j, n) {
                cin >> d[i][j];
                //cities[i].d = d;
            }
        }
        forf(i, q) {
            cin >> u[i] >> v[i];
            u[i]--;
            v[i]--;
        }
        /*
        sort(cities.begin(), cities.end());
        stack stk;
        vi next_faster(n);
        forb(i, n) {
            while (!stk.empty() && stk.top().s <= cities[i].s) {
                stk.pop();
            }
            next_faster[i] = (stk.empty() ? 0 : stk.top());
            stk.push(cities[i]);
        }
        */
        vector<vector<long double> > min_time(n, vector<long double>(n));
        forf(i, n) {
            forf(j, n) {
                min_time[i][j] = 1000000000000000000.0;
            }
        }
        forf(i, n) {
            min_time[i][i] = 0;
            if (i < n - 1) {
                min_time[i][i + 1] = (long double) d[i][i + 1] / s[i];
            }
        }
        forb(i, n - 2) {
            ll running_dist = d[i][i + 1];
            long double running_min_time = min_time[i][i + 1];
            for (int j = i + 2; j < n; j++) {
                running_dist += d[j - 1][j];
                if (running_dist <= e[i]) {
                    min_time[i][j] = (long double) running_dist / s[i];
                }
                for (int k = i + 1; k < j; k++) {
                    min_time[i][j] = min(min_time[i][j], min_time[i][k] + min_time[k][j]);
                }
            }
        }
		cout << "Case #" << t << ":";
        forf(i, q) {
            cout << fixed << setprecision(7) << ' ' << min_time[u[i]][v[i]];
        }
        cout << '\n';
	}
	return 0;
}
