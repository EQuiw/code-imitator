#include <stdio.h>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <assert.h>
using namespace std;

#define INF 987654321987654321LL

int ck[101];
int N, P;
int G[101];

int solve(int x, int n, int m, int sum) {
	ck[x] = true;

	if (m == n) {
		if (sum % P == 0) {
			return 1;
		}
	}
	else {
		for (int i = x + 1; i < N; i++) {
			if (!ck[i]) {
				if (solve(i, n, m + 1, sum + G[i])) {
					return 1;
				}
			}
		}
	}

	ck[x] = false;
	return 0;
}

int main() {
	int T;
	freopen("A-small-attempt0.in", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d", &T);
	
	for(int testCase = 1; testCase <= T; testCase++) {

		scanf("%d %d", &N, &P);

		for (int i = 0; i < N; i++) {
			scanf("%d", &G[i]);
			ck[i] = 0;
		}

		int x = 0;

		for (int i = 0; i < N; i++) {
			x += (G[i] % P) == 0;
		}

		sort(G, G + N, [](int A, int B) {
			return A % P < B % P;
		});


		printf("Case #%d: ", testCase);
		int res = 0;

		for (int i = 1; i <= P; i++) {
			for (int j = 0; j < N; j++) {
				if (!ck[j] && solve(j, i, 1, G[j])) {
					res++;
				}
			}
		}

		int addition = 0;
		for (int i = 0; i < N; i++) {
			if (ck[i] == 0) {
				addition = 1;
			}
		}

		printf("%d\n", res + addition);
	}

	return 0;
}