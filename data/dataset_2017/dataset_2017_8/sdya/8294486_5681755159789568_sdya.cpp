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

const int maxN = 110;
const long long inf = 1000000000000000000LL;

int n, q;
long long d[maxN][maxN];
long long e[maxN], s[maxN];

long long a[maxN], b[maxN];

double c[maxN];

double solve(int u, int v) {
	--u;
	--v;

	for (int i = 0; i < n; ++i) {
		c[i] = 1e50;
	}
	c[u] = 0.0;

	for (int steps = 0; steps < 200; ++steps) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (i == j || d[i][j] == inf || e[i] < d[i][j]) {
					continue;
				}
				c[j] = min(c[j], c[i] + (double)(d[i][j]) / (double)(s[i]));
			}
		}
	}
	return c[v];
}

void solve(int test) {
	cin >> n >> q;
	for (int i = 0; i < n; ++i) {
		cin >> e[i] >> s[i];
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> d[i][j];
			if (d[i][j] == -1) {
				d[i][j] = inf;
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k) {
				d[j][k] = min(d[j][k], d[j][i] + d[i][k]);
			}
		}
	}

	vector < double > res;
	for (int i = 0; i < q; ++i) {
		int u, v;
		cin >> u >> v;
		res.push_back(solve(u, v));
	}

	printf("Case #%d:", test);
	for (int i = 0; i < q; ++i) {
		printf(" %.10lf", res[i]);
	}
	printf("\n");
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
		} else {
			readData();
		}
		cerr << i << ": " << clock() << endl;
	}

	return 0;
}
