#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	int tt;
	cin >> tt;
	for (int t = 1; t <= tt; ++t) {
		int d, n;
		cin >> d >> n;
		double ti = 0;
		for (int i = 0; i < n; ++i) {
			int k, s;
			cin >> k >> s;
			ti = max(ti, (d - k) / double(s)); 
		}
		cout << "Case #" << t << ": " << fixed << setprecision(20) << d / ti << endl;
	}
}