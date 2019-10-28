#include<bits/stdc++.h>
char str[1010];
char filp(char ch) {
	if (ch == '+')return '-';
	return '+';
}
int main() {
	int tc;
	scanf("%d", &tc);
	int p = 0;
	while (tc--) {
		int k;
		scanf("%s%d",  str, &k);
		int cnt = 0;
		for (int i = 0; str[i + k-1] != '\0'; i++) {
			if (str[i] == '-') {
				cnt++;
				for (int j = 0; j < k; j++) {
					str[i + j] = filp(str[i + j]);
				}
			}
		}
		for (int i = 0; str[i] != '\0'; i++) {
			if (str[i] == '-') {
				cnt = -1;
				break;
			}
		}
		p++;
		if (cnt == -1) {
			printf("Case #%d: IMPOSSIBLE\n", p);
		}
		else {
			printf("Case #%d: %d\n", p, cnt);
		}
	}
}