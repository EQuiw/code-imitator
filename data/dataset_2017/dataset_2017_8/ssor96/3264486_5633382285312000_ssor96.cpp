#include <iostream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	for (int q = 1; q <= t; ++q) {
		string s;
		cin >> s;
		int n = s.size();
		cout << "Case #" << q << ": ";
		for (int i = 1; i < n; ++i) {
			if (s[i] < s[i - 1]) {
				for (int j = i; j < n; ++j) s[j] = '9';
				if (s[i - 1] == '0') s[i - 1] = '9';
				else s[i - 1]--;
				i--;
				while (i && s[i] < s[i - 1]) {
					s[i] = '9';
					if (s[i - 1] == '0') s[i - 1] = '9';
					else s[i - 1]--;
					i--;
				}
				break;
			}
		}
		long long int ans = 0;
		for (int i = 0; i < n; ++i) {
			ans = ans * 10 + s[i] - '0';
		}
		cout << ans << endl;
	}
}