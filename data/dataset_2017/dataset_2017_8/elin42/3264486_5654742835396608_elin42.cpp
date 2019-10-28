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

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
        int n, k;
        cin >> n >> k;
        priority_queue<int> q;
        q.push(n);
        int y = -1, z = -1;
        forf(i, k) {
            int len = q.top();
            q.pop();
            q.push(len/2);
            y = len/2;
            if (2*y == len) {
                q.push(y - 1);
                z = y - 1;
            } else {
                q.push(y);
                z = y;
            }
        }
		cout << "Case #" << t << ": ";
        cout << y << ' ' << z << '\n';
	}
	return 0;
}
