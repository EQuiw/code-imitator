#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	int tt;
	cin >> tt;
	for (int t = 1; t <= tt; ++t) {
		int a, b;
		cin >> a >> b;
		int ans;
		if (a == 0) {
			if (b == 1) {
				int b, e;
				cin >> b >> e;
				ans = 2;
			}
			else {
				int b1, e1, b2, e2;
				cin >> b1 >> e1 >> b2 >> e2;
				int e = max(e1, e2);
				int b = min(b1, b2);
				int ee = min(e1, e2);
				int bb = max(b1, b2);
				if (e - b <= 720) {
					ans = 2;
				}
				else if (bb - ee >= 720) {
					ans = 2;
				}
				else {
					ans = 4;
				}
			}
		}
		else if (a == 1) {
			if (b == 1) {
				int b1, e1, b2, e2;
				cin >> b1 >> e1 >> b2 >> e2;
				
				ans = 2;
			}
			else {
				int b, e;
				cin >> b >> e;
				ans = 2;
			}
		}
		else {
			int b1, e1, b2, e2;
			cin >> b1 >> e1 >> b2 >> e2;
			int e = max(e1, e2);
			int b = min(b1, b2);
			int ee = min(e1, e2);
			int bb = max(b1, b2);
			if (e - b <= 720) {
				ans = 2;
			}
			else if (bb - ee >= 720) {
				ans = 2;
			}
			else {
				ans = 4;
			}
		}
		cout << "Case #" << t << ": " << ans << endl;
	}
}