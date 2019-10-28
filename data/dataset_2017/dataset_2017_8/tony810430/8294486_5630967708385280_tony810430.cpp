#include <stdio.h>
#include <algorithm>
using namespace std;

int T, cas;
long long D;
int N;

int main()
{
	long long K, S;
	double t;

	scanf(" %d", &T);
	for (cas = 1; cas <= T; cas++) {
		scanf(" %lld %d", &D, &N);
		t = 0.0;

		for (int i = 0; i < N; i++) {
			scanf(" %lld %lld", &K, &S);
			double dis = D - K;
			t = max(t, dis/S);
		}

		printf("Case #%d: %.8lf\n", cas, D/t);
	}

	return 0;
}