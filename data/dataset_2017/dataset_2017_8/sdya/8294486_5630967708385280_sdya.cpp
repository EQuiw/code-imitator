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

const int maxN = 1100;
double d;
long long n;
double s[maxN], k[maxN];

void solve(int test) {
	if (test == 29) {
		int f = 0;
	}
	cin >> d >> n;
	for (int i = 0; i < n; ++i) {
		cin >> k[i] >> s[i];
	}

	double l = 0.0, r = 1e18;
	for (int t = 0; t < 400; ++t) {
		double m = (l + r) / 2.0;
		bool ok = true;

		double p = d / m;
		for (int j = 0; j < n; ++j) {
			if (k[j] + s[j] * p < d) {
				ok = false;
				break;
			}
		}

		if (ok) {
			l = m;
		} else {
			r = m;
		}
	}

	printf("Case #%d: %.10lf\n", test, (l + r) / 2.0);
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
