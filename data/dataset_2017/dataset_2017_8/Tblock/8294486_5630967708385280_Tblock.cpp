#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

#define EPS 1e-9

using namespace std;

typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<int> vi;
typedef vector<vi> vvi;



int main() {

	int t; cin >> t;
	int cas = 1;
	while (t--) {
		cout << "Case #" << cas << ": ";
		cas++;

		int d, n; cin >> d >> n;
		double max = -1e300;
		for (int i = 0; i < n; i++) {
			int ki, si; cin >> ki >> si;
			double t = (double)(d - ki) / si;
			if (t > max) {
				max = t;
			}
		}

		// slowest horse takes min time to reach the end
		cout << fixed << setprecision(10) << (double)d / max << endl;
	}

	return 0;
}