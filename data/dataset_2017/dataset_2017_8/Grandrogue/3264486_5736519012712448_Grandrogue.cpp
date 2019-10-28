#include <fstream>
#include <string>

using namespace std;

ifstream fin("A-small-attempt0.in");
ofstream fout("out.txt");

int main() {
	int t;
	fin >> t;
	for (int _t = 0; _t < t; ++_t)  {
		string s;
		int ans = 0;
		int k;

		fin >> s >> k;
		for (int i = 0; i <= s.length() - k; ++i) {
			if (s[i] == '-') {
				for (int j = i; j < i + k; ++j) {
					s[j] = s[j] == '-' ? '+' : '-';
				}

				++ans;
			}
		}

		for (int i = s.length() - k + 1; i < s.length(); ++i) {
			if (s[i] == '-') {
				ans = -1;
				break;
			}
		}

		fout << "Case #" << _t + 1 << ": ";
		if (ans == -1) {
			fout << "IMPOSSIBLE" << endl;
		} else {
			fout << ans << endl;
		}
	}

	return 0;
}