#include <iostream>
#include <vector>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	
	int tt;
	cin >> tt;
	for (int t = 1; t <= tt; ++t) {
		int n, m;
		cin >> n >> m;
		vector <string> ar(n);
		vector <vector <bool> > used(n, vector <bool> (m, false));
		for (int i = 0; i < n; ++i) {
			cin >> ar[i];
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (ar[i][j] != '?' && !used[i][j]) {
					int l = j;
					int r = j;
					int u = i;
					int d = i;
					while (l >= 1 && ar[i][l - 1] == '?') l--;
					while (r <= m - 2 && ar[i][r + 1] == '?') r++;
					for (;u >= 1;) {
						bool f = true;
						for (int jj = l; jj <= r; ++jj) {
							if (ar[u - 1][jj] != '?') {
								f = false;
								break;
							}
						}
						if (!f) break;
						else --u;
					}
					for (;d <= n - 2;) {
						bool f = true;
						for (int jj = l; jj <= r; ++jj) {
							if (ar[d + 1][jj] != '?') {
								f = false;
								break;
							}
						}
						if (!f) break;
						else ++d;
					}
					for (int ii = u; ii <= d; ++ii) {
						for (int jj = l; jj <= r; ++jj) {
							ar[ii][jj] = ar[i][j];
							used[ii][jj] = true;
						}
					}
				}
			}
		}
		cout << "Case #" << t << ":" << endl;
		for (int i = 0; i < n; ++i) {
			cout << ar[i] << endl;
		}
	}
}