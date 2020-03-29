#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;

typedef long long lld;

#define FILENAME "A-small-attempt0"

int main() {
	int T;
	freopen("A-small-attempt0.in", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d", &T);

	for (int testCase = 1; testCase <= T; testCase++) {
		int N, K;

		vector<pair<lld, lld> > P;
		scanf("%d %d", &N, &K);

		for (int i = 0; i < N; i++) {
			pair<lld, lld> p;
			scanf("%lld %lld", &p.first, &p.second);

			P.push_back(p);
		}


		lld res = 0;

		sort(P.begin(), P.end(), [](const pair<lld, lld> &A, const pair<lld, lld> &B) {
			return A.first > B.first || (A.first == B.first && A.second > B.second);
		});
		for (auto it = P.begin(); it != P.end() - K + 1; it++) {
			vector<pair<lld, lld> > tmpV(it + 1, P.end());
			lld tmp = it->first * it->first + 2 * it->first * it->second;

			sort(tmpV.begin(), tmpV.end(), [](const pair<lld, lld> &A, const pair<lld, lld> &B) {
				return A.first * A.second > B.first * B.second;
			});

			for (int i = 0; i < K - 1; i++) {
				tmp += tmpV[i].first * tmpV[i].second * 2;
			}

			if (res < tmp)
				res = tmp;
		}

		printf("Case #%d: ", testCase);

		printf("%.6lf\n", res * M_PI);

	}

	return 0;
}