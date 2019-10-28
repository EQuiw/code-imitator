#include<bits/stdc++.h>

using namespace std;

int main() {
	int test;
	cin >> test;
	for (int cases = 1; cases <= test; cases++) {
		int D, N;
		cin >> D >> N;
		double maxTm = 0;
		for (int i = 0; i < N; i++) {
			int k, s;
			cin >> k >> s;
			double tm = 1.0 * (D - k) / s;
			if (tm > maxTm) maxTm = tm;
		}
		double sp = D / maxTm;
		printf("Case #%d: %.8lf\n", cases, sp);
	}
	return 0;
}
