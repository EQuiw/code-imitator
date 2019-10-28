#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
	freopen("A-small-attempt0.in", "r", stdin);
	freopen("A-small-attempt0.out", "w", stdout);

	int T;
	cin >> T;
	for (int test = 1; test <= T; ++test) {
		string s;
		int k;
		cin >> s >> k;
		int r = 0;
		for (int i = 0; i + k - 1 < s.size(); ++i) {
			if (s[i] == '-') {
				++r;
				for (int j = 0; j < k; ++j) {
					s[i + j] = (s[i + j] == '+' ? '-' : '+');
				}
			}
		}
		for (int i = s.size() + 1 - k; i < s.size(); ++i) {
			if (s[i] == '-') {
				r = -1;
				break;
			}
		}
		if (r == -1) {
			cout << "Case #" << test << ": IMPOSSIBLE" << endl;
		} else {
			cout << "Case #" << test << ": " << r << endl;
		}
	}

	return 0;
}
