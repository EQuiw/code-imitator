/******************************************
*    AUTHOR:         BHUVNESH JAIN        *
*    INSTITUITION:   BITS PILANI, PILANI  *
******************************************/
#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL; 
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL, LL> pll;

set<int> u, v;

int main() {
	ios_base::sync_with_stdio(false);
	int t, n, k, a, b, c;
	cin >> t;
	for(int T = 1; T <= t; ++T) {
		cout << "Case #" << T << ": ";
		
		cin >> n >> k;
		a = 0;
		b = 0;
		if (n == k) {
			cout << b << " " << a << "\n";
			continue;
		}
		u.clear();
		v.clear();
		for(int i = 1; i <= n; ++i) {
			u.insert(i);
		}
		v.insert(0);
		v.insert(n+1);
		for(int i = 1; i <= k; ++i) {
			a = -1, b = -1, c = 0;
			for(int x : u) {
				auto it = v.lower_bound(x);
				int f = (*it) - x - 1;
				// cout << (*it) << " : ";
				it--;
				// cout << (*it) << " : ";
				int g = x - (*it) - 1;
				if (min(f, g) > a) {
					a = min(f, g);
					b = max(f, g);
					c = x;
				}
				else if (min(f, g) == a) {
					if (max(f, g) > b) {
						a = min(f, g);
						b = max(f, g);
						c = x;
					}
				}
				// cout << x << " " << f << " " << g << "\n";
			}
			// cout << c << "\n";
			assert(c != 0);
			u.erase(c);
			v.insert(c);
		}
		cout << b << " " << a << "\n";
	}
	return 0;
}