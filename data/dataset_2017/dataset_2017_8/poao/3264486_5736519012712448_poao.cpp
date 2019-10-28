#include <cstdio>
#include <cstring>

int T, K, N;
char cake[1010];

int main() {
	freopen("A-small-attempt0.in", "r", stdin);
	freopen("A-small-attempt0.out", "w", stdout);
	scanf("%d", &T);
	for(int tc=1; tc<=T; tc++) {
		scanf("%s%d", cake, &K);
		int ans = 0;
		bool pos = true;
		N = strlen(cake);
		for(int i=0; i<=N-K; i++) {
			if(cake[i] == '-')  {
				ans++;
				for(int j=0; j<K; j++) {
					if(cake[i+j] == '-') {
						cake[i+j] = '+';
					}
					else {
						cake[i+j] = '-';
					}
				}
			}
		}
		for(int i=N-K; i<N; i++) {
			if(cake[i]  == '-') {
				pos = false;
				break;
			}
		}
		if(pos) {
			printf("Case #%d: %d\n", tc, ans);
		}
		else {
			printf("Case #%d: IMPOSSIBLE\n", tc);
		}
	}
	return 0;
}
