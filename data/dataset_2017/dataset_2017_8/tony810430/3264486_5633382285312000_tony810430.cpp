#include <stdio.h>
#include <string.h>


int main()
{
	int T;
	char S[20];
	int N[20];

	scanf(" %d", &T);
	for (int cas = 1; cas <= T; cas++) {
		scanf(" %s", S);
		int len = strlen(S);
		for (int i = 0; i < len; i++) {
			N[i] = S[i] - '0';
		}

		for (int i = len-1; i > 0; i--) {
			if (N[i-1] > N[i]) {
				N[i-1]--;
				for (int j = i; j < len; j++) {
					N[j] = 9;
				}
			}
		}

		printf("Case #%d: ", cas);
		int i = 0;
		for (; i < len; i++) {
			if (N[i] != 0) break;
		}
		for (; i < len; i++) {
			printf("%d", N[i]);
		}
		puts("");
	}

	return 0;
}