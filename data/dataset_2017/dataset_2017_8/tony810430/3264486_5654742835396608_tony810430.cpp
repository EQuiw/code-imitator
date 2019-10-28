#include <stdio.h>


int main()
{

	int T;
	long long N;
	long long K;
	
	scanf(" %d", &T);
	for (int cas = 1; cas <= T; cas++) {
		scanf(" %lld %lld", &N, &K);

		while (K >= 1) {
			N--;
			if (K == 1) {
				printf("Case #%d: %lld %lld\n", cas, (N/2)+((N%2)==0?0:1), N/2);
				break;
			}
			K--;

			if ((K%2) == 0) {
				K /= 2;
				N /= 2;
			} else {
				K = K/2 + 1;
				N = (N/2) + ((N%2)==0?0:1);
			}
		}
	}
	return 0;
}