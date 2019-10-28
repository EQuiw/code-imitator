#include<bits/stdc++.h>

using namespace std;

int n, m;

int main() {
	int test;
	cin >> test;
	for (int cases = 1; cases <= test; cases++) {
		cin >> n >> m;
		vector<string> v;
		for (int i = 0; i < n; i++) {
			string s;
			cin >> s;
			v.push_back(s);
		}

		for (int j = 0; j < m; j++) {
			for (int i = 0; i < n; i++) {
				if (v[i][j] != '?') {
					for (int k = 0; k < i; k++) {
						if (v[k][j] == '?') v[k][j] = v[i][j];
					}
				}
			}
		}

		// fill bottom section
		for (int i = 1; i < n; i++)
			for (int j = 0; j < m; j++) {
				if (v[i][j] == '?' && v[i-1][j] != '?') {
					for (int k = i; k < n; k++)
						if (v[k][j] == '?')
							v[k][j] = v[i-1][j];
				}
			}

		// fill left
		for (int i = 0; i < n; i++)
			for (int j = 0; j + 1 < m; j++) {
				if (v[i][j] == '?' && v[i][j+1] != '?') {
					for (int k = 0; k <= j; k++) {
						if (v[i][k] == '?') v[i][k] = v[i][j+1];
					}
				}
			}

		// fill right
		for (int i = 0; i < n; i++) {
			for (int j = m - 1; j > 0; j--) {
				if (v[i][j] == '?' && v[i][j-1] != '?') {
					for (int k = j; k < m; k++) {
						if (v[i][k] == '?') v[i][k] = v[i][j-1];
					}
				}
			}
		}
		printf("Case #%d:\n", cases);
		for (int i = 0; i < n; i++)
			cout << v[i] << endl;
	}
	return 0;
}
