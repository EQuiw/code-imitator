#include <stdio.h>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

struct State {
	int Hd, Ad, Hk, Ak, Depth;
};

string toS(State s) {
	char buf[5000];

	sprintf(buf, "%d,%d,%d,%d,%d,%d", s.Hd, s.Ad, s.Hk, s.Ak, s.Depth);

	return string(buf);
}
int main() {
	int T;
	freopen("A-small-attempt2.in", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d", &T);
	
	for(int testCase = 1; testCase <= T; testCase++) {
		long long D;
		int N;
		scanf("%lld %d", &D, &N);

		long long K[1001], S[1001];

		double res;

		for (int i = 0; i < N; i++) {
			scanf("%lld %lld", &K[i], &S[i]);
		}

		pair<long long, long long> maxTime = { 0, 1 };

		for (int i = 0; i < N; i++) {
			if (maxTime.first * S[i] < maxTime.second * (D - K[i])) {
				maxTime = make_pair(D - K[i], S[i]);
			}
		}

		res = (double)maxTime.second * D / (double)maxTime.first;

		printf("Case #%d: %.6lf\n", testCase, res);
	}

	return 0;
}