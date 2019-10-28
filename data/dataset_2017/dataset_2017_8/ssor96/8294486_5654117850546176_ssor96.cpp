#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

// o -> b
// g -> r
// v -> y

int main() {
	ios_base::sync_with_stdio(false);
	int tt;
	cin >> tt;
	for (int t = 1; t <= tt; ++t) {
		int n, r, o, y, g, b, v;
		cin >> n >> r >> o >> y >> g >> b >> v;
		string s(n, '?');
		//vector <vector<pair<vector<int>, string> > > ar(2, vector<pair<vector<int>, string> >(3));
		vector <pair<int, char> > ar(3);
		// for (int i = 0; i < 3; ++i) {
		// 	ar[0].first[j] = r;
		// 	ar[1].first[j] = y;
		// 	ar[2].first[j] = b;
		// }
		ar[0] = make_pair(-r, 'R');
		ar[1] = make_pair(-y, 'Y');
		ar[2] = make_pair(-b, 'B');
		sort(ar.begin(), ar.end());
		char prev = 'Q';
		bool f = true;
		char fir = ar[0].second;
		for (int i = 0; i < n; ++i) {
			sort(ar.begin(), ar.end());
			// cout << s << endl;
			// for (int j = 0; j < 3; ++j) {
			// 	cout << -ar[j].first << " " << ar[j].second << endl;
			// }
			// cout << "prev = " << prev << endl;
			if (ar[0].first == ar[1].first && prev != fir) {
				if (ar[0].second == fir) {
					s[i] = fir;
					ar[0].first++;
					prev = fir;
					continue;
				}
				else if (ar[1].second == fir) {
					s[i] = fir;
					ar[1].first++;
					prev = fir;
					continue;
				}
				else if (ar[2].first == ar[0].first) {
					s[i] = fir;
					ar[2].first++;
					prev = fir;
					continue;
				}
			}
			for (int j = 0; j < 3; ++j) {
				if (ar[j].first == 0) {
					f = false;
					break;
				}
				if (prev != ar[j].second) {
					ar[j].first++;
					s[i] = ar[j].second;
					prev = ar[j].second;
					break;
				}
			}
			if (!f) break;
		}
		if (!f || s[0] == s[n - 1]) s = "IMPOSSIBLE";
		cout << "Case #" << t << ": " << s << endl;
	}
}