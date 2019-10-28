#include <stdio.h>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
using namespace std;
int main() {
	int T;
	freopen("C-small-1-attempt2.in", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d", &T);
	
	for(int testCase = 1; testCase <= T; testCase++) {
		long long N, K, cnt, step;
		cin >> N >> K;

		cnt = 1;
		step = 1;

		while (K > step) {
			K -= step;
			if (N % 2 == 1) {
				long long tmp = step - cnt;
				cnt *= 2;
				cnt += tmp;
			}
			step <<= 1;
			N /= 2;
		}

		printf("Case #%d: ", testCase);

		if (K <= cnt) {
			printf("%lld %lld", N / 2, (N - 1) / 2);
		}
		else {
			printf("%lld %lld", (N - 1) / 2, (N - 2) / 2);
		}
		printf("\n");
	}

	return 0;
}