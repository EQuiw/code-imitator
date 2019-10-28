#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

int TC, ans, n, k;
char a[1111];

void work() {
	ans = 0;
	scanf("%s%d", a, &k);
	n = strlen(a);
	for (int i = 0; i < n; ++i) {
		if (a[i] == '-') {
			if (i + k > n) {
				printf("IMPOSSIBLE\n");
				return;
			}
			for (int j = i; j < i + k; ++j) {
				a[j] = a[j] == '-' ? '+':'-';
			}
			ans++;
		}
	}
	printf("%d\n", ans);
}

int main() {
	freopen("A-small-attempt0.in", "r", stdin);
	freopen("A.out", "w", stdout);
	scanf("%d", &TC);
	for (int tc = 1; tc <= TC; ++tc) {
		printf("Case #%d: ", tc);
		work();
	}
	
}