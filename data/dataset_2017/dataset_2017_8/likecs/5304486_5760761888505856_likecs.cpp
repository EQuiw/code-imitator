/******************************************
*    AUTHOR:         BHUVNESH JAIN        *
*    INSTITUITION:   BITS PILANI, PILANI  *
******************************************/
#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL; 
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL, LL> pll;

const int MAX = 30;

string s[MAX], a[MAX];
int g[MAX][MAX];

int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	for(int T = 1; T <= t; ++T) {
		cout << "Case #" << T << ":\n";
		int r, c;
		cin >> r >> c;
		for(int i = 0; i < r; ++i) {
			cin >> s[i];
			for(int j = 0; j < c; ++j) {
				g[i][j] = (s[i][j] != '?');
			}
		}
		for(int i = 0; i < r; ++i) {
			a[i] = s[i];
		}
		for(int step = 1; step <= 5; ++step) {
			for(int i = 0; i < r; ++i) {
				for(int j = 0; j < c; ++j) {
					if (g[i][j] == 1) {
						int u = i, d = i, l = j, q = j+1;
						while(u >= 0) {
							bool can = true;
							for(int k = l; k < q; ++k) {
								if (a[u][k] == '?' || a[u][k] == a[i][j]) {
									//
								}
								else {
									can = false;
									break;
								}
							}
							if (!can) break;
							u -= 1;
						}
						while(d < r) {
							bool can = true;
							for(int k = l; k < q; ++k) {
								if (a[d][k] == '?' || a[d][k] == a[i][j]) {
									//
								}
								else {
									can = false;
									break;
								}
							}
							if (!can) break;
							d += 1;
						}
						if (step == 1) {
							l -= 1;
						}
						while(step > 1 && l >= 0) {
							bool can = true;
							for(int k = u+1; k <= d-1; ++k) {
								if (a[k][l] == '?' || a[k][l] == a[i][j]) {
									//
								}
								else {
									can = false;
									break;
								}
							}
							if (!can) break;
							l -= 1;
						}
						while(q < c) {
							bool can = true;
							for(int k = u+1; k <= d-1; ++k) {
								if (a[k][q] == '?' || a[k][q] == a[i][j]) {
									//
								}
								else {
									can = false;
									break;
								}
							}
							if (!can) break;
							q += 1;
						}
						// printf("%c %d %d : %d %d %d %d\n", a[i][j], i, j, u+1, d-1, l+1, q-1);
						for(int x = u+1; x <= d-1; ++x) {
							for(int y = l+1; y <= q-1; ++y) {
								a[x][y] = a[i][j];
							}
						}
					}
				}
			}
			// printf("\n");
		}	
		bool done = true;
		for(int i = 0; i < r; ++i) {
			for(int j = 0; j < c; ++j) {
				done &= (a[i][j] != '?');
				if (s[i][j] != '?') {
					assert(a[i][j] == s[i][j]);
				}
			}
		}
		assert(done);
		for(int i = 0; i < r; ++i) {
			cout << a[i] << "\n";
		}
	}
	return 0;
}