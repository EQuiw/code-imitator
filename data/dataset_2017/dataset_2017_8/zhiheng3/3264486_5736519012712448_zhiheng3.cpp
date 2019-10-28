#include <iostream>
#include <string>

using namespace std;

int main() {
	int T;
	cin >> T;
	for (int c = 1; c <= T; ++c) {
		string s;
		int k, result = 0;;
		cin >> s >> k;
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] == '-') {
				++result;
				if (i + k > s.size()) {
					result = -1;
					break;
				}
				for (int j = i; j < i + k; ++j) {
					if (s[j] == '-') {
						s[j] = '+';
					} else {
						s[j] = '-';
					}
				}
			}
		}
		cout << "Case #" << c << ": ";
		if (result == -1) {
			cout << "IMPOSSIBLE" << endl;
		} else {
			cout << result << endl;
		}
	}
	return 0;
}