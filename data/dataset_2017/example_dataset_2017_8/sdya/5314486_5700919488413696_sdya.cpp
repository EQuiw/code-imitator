#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <cmath>
#include <ctime>
#pragma comment (linker, "/STACK:256000000")

using namespace std;

void readData() {
}

const int maxN = 105;
int d[maxN][maxN][maxN][maxN];
int n, p;
int a[maxN];
int c[4];


void solve(int test) {
	cin >> n >> p;
	for (int i = 0; i < 4; ++i) {
		c[i] = 0;
	}
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		++c[a[i] % p];
	}
	memset(d, -1, sizeof(d));
	d[0][0][0][0] = 0;
	for (int i = 0; i <= c[0]; ++i) {
		for (int j = 0; j <= c[1]; ++j) {
			for (int k = 0; k <= c[2]; ++k) {
				for (int l = 0; l <= c[3]; ++l) {
					if (d[i][j][k][l] == -1) {
						continue;
					}
					int rem = (j + 2 * k + 3 * l) % p;
					int added = (int)(rem == 0);
					d[i + 1][j][k][l] = max(d[i + 1][j][k][l], d[i][j][k][l] + added);
					d[i][j + 1][k][l] = max(d[i][j + 1][k][l], d[i][j][k][l] + added);
					d[i][j][k + 1][l] = max(d[i][j][k + 1][l], d[i][j][k][l] + added);
					d[i][j][k][l + 1] = max(d[i][j][k][l + 1], d[i][j][k][l] + added);
				}
			}
		}
	}
	printf("Case #%d: %d\n", test, d[c[0]][c[1]][c[2]][c[3]]);
}

int main(int argc, char* argv[]) {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int left_bound, right_bound;

	/*freopen(argv[3], "w", stdout);	
	sscanf(argv[1], "%d", &left_bound);
	sscanf(argv[2], "%d", &right_bound);*/

	int t;
	cin >> t;
	left_bound = 1, right_bound = t;
	for (int i = 1; i <= t; ++i) {
		if (i >= left_bound && i <= right_bound) {
			solve(i);
		}
		cerr << i << ": " << clock() << endl;
	}

	return 0;
}
