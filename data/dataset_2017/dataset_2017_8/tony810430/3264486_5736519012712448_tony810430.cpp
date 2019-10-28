#include <stdio.h>
#include <string.h>

int main()
{
	int T;
	char S[2000];
	int K;

	scanf(" %d", &T);
	for (int cas = 1; cas <= T; cas++) {
		scanf(" %s %d", S, &K);

		int len = strlen(S);

		int res = 0;
		for (int i = 0; i < len; i++) {
			if (S[i] == '-') {
				if (i+K <= len) {
					res++;
					for (int j = i; j < i+K; j++) {
						S[j] = (S[j] == '+') ? '-' : '+';
					}
				} else {
					res = -1;
				}
			}
		}

		if (res < 0) {
			printf("Case #%d: IMPOSSIBLE\n", cas);
		} else {
			printf("Case #%d: %d\n", cas, res);
		}

	}

	return 0;
}