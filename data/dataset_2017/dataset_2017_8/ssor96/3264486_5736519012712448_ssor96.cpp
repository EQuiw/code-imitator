#include <iostream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	for (int q = 1; q <= t; ++q) {
		string s;
		cin >> s;
		int k;
		cin >> k;
		int n = s.size();
		int ans = 0;
		cout << "Case #" << q << ": ";
		for (int i = 0; i <= n - k; ++i) {
			if (s[i] == '-') {
				for (int j = 0; j < k; ++j) {
					if (s[i + j] == '-') s[i + j] = '+';
					else s[i + j] = '-';
				}
				ans++;
			}
		}
		for (int i = n - k; i < n; ++i) {
			if (s[i] == '-') ans = -1;
		}
		if (ans == -1) {
			cout << "IMPOSSIBLE" << endl;
		}
		else {
			cout << ans << endl;
		}
	}
}