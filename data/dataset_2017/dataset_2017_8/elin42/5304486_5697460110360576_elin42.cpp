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

bool approx(int q, int kit_amt) {
    return 10*q >= 9*kit_amt && 10*q <= 11*kit_amt;
}

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
        int n, p;
        cin >> n >> p;
        vi r(n);
        forf(i, n) {
            cin >> r[i];
        }
        vvi q(n, vi(p));
        //int maxServings = 0;
        forf(i, n) {
            forf(j, p) {
                cin >> q[i][j];
                //maxServings = max(maxServings, q[i][j] / r[i] + 1);
            }
            sort(q[i].begin(), q[i].end());
        }
        int ans = 0;
        /*
        for (int servings = 1; servings <= maxServings; servings++) {
            vi choices(n);
            int small_ans = 1;
            forf(i, n) {
                int lb = (r[i] * servings * 9 + 5) / 10;
                int ub = r[i] * servings * 11 / 10;
                int first = -1, last = -1;
                int lo = 0, hi = p - 1;
                while (lo <= hi) {
                    int mid = lo + (hi - lo)/2;
                    if (q[i][mid] < lb) {
                        lo = mid + 1;
                    } else {
                        first = mid;
                        hi = mid - 1;
                    }
                }
                lo = 0, hi = p - 1;
                while (lo <= hi) {
                    int mid = lo + (hi - lo)/2;
                    if (q[i][mid] > ub) {
                        hi = mid - 1;
                    } else {
                        last = mid;
                        lo = mid + 1;
                    }
                }
                if (first != -1 && first <= last) {
                    choices[i] = last - first + 1;
                    small_ans *= choices[i];
                } else {
                    small_ans = 0;
                }
            }
            cout << servings << ' ' << small_ans << '\n';
            ans += small_ans;
        }
        */
        if (n == 1) {
            forf(a, p) {
                int kit_amt = q[0][a] / r[0] * r[0];
                if (approx(q[0][a], kit_amt) || approx(q[0][a], kit_amt + 1)) {
                    ans++;
                }
            }
        } else {
            forf(a, p) {
                forf(b, p) {
                    double frac_a = (double) q[0][a] / r[0];
                    double frac_b = (double) q[1][b] / r[1];
                    bool x = false;
                    for (int servings = min(frac_a, frac_b); servings <= max(frac_a, frac_b) + 1; servings++) {
                        if (approx(q[0][a], r[0]*servings) && approx(q[1][b], r[1]*servings)) {
                            x = true;
                        }
                    }
                    if (x) {
                        ans++;
                    }
                    /*
                    if (frac_a <= servings * 1.1 && frac_a >= servings * 0.9
                            && frac_b <= servings * 1.1 && frac_b >= servings * 0.9) {
                        can = true;
                    }
                    servings++;
                    if (frac_a <= servings * 1.1 && frac_a >= servings * 0.9
                            && frac_b <= servings * 1.1 && frac_b >= servings * 0.9) {
                        can = true;
                    }
                    if (can) {
                        ans++;
                    }
                    */
                }
            }
        }
		cout << "Case #" << t << ": " << ans << '\n';
	}
	return 0;
}
