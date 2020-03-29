#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

char ch[10], p[111][111], o[111][111];
int n, m, match1[300], match2[300], ans, a[11111], b[11111], c[11111], ct;
bool v1[300], v2[300], v[300], e[300][300];

bool dfs(int x) {
	for (int i = 2; i <= 2 * n; ++i) {
		if (e[x][i]) {
			//printf("e %d %d\n", x, i);
			if (!v[i]) {
				v[i] = true;
				if (match2[i] == 0 || dfs(match2[i])) {
					match1[x] = i;
					match2[i] = x;
					return true;
				}
			}
		}

	}
	return false;
}

void work() {
	scanf("%d%d", &n, &m);
	memset(v1, 0, sizeof(v1));
	memset(v2, 0, sizeof(v2));
	memset(e, 0, sizeof(e));
	memset(p, 0, sizeof(p));
	memset(o, 0, sizeof(o));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			e[i-j+n][i+j] = 1;//;e[i+j][i-j+n] = 1;
			//printf("%d %d\n", i-j, i+j);
		}
	}
	ans = ct=0;
	for (int i = 0; i < m; ++i) {
		int x, y;
		scanf("%s%d%d", ch, &x, &y);
		o[x][y] = ch[0];
		if (ch[0] != 'x') {
			for (int j = 1; j <= n*2; ++j) {
				e[x-y+n][j] = 0;
				e[j][x+y] = 0;
			}
		}
		if (ch[0] != '+') {
			v1[x] = 1;
			v2[y] = 1;
		}
		ans += ch[0] == 'o' ? 2 : 1;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (!v1[i] && !v2[j]) {
				p[i][j] = 'x';
				ans += 1;
				v1[i] = v2[j] = true;
			}
		}
	}
	//printf("%d\n", ans);
	memset(match1, 0, sizeof(match1));
	memset(match2, 0, sizeof(match2));
	memset(v, 0, sizeof(v));
	for (int i = 1; i < n * 2; ++i) {
		if (!match1[i]) {
			memset(v, 0, sizeof(v));
			if (dfs(i)) {
				ans++;
				//printf("i=%d %d %d %d\n", i-n, match1[i], (i-n+match1[i])/2, (match1[i]-i+n)/2);
			}
		}
	}
	for (int i = 1; i < n*2; ++i) {
		if (match1[i]) {
			int l = i - n, r = match1[i];
			int x = (l + r)/2, y = (r - l)/2;
			if (!p[x][y]) p[x][y] = '+';
			else p[x][y] = 'o';
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (p[i][j]) ct++;
		}
	}
	printf("%d %d\n", ans, ct);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n;++j){
			if (p[i][j]) {
				if (o[i][j]) printf("o %d %d\n", i, j);
				else printf("%c %d %d\n", p[i][j], i, j);
			}
		}
	}


}

int main() {
	int TC;
	freopen("D-small-attempt1.in", "r", stdin);
	freopen("D-small-attempt1.out", "w", stdout);
	scanf("%d", &TC);
	for (int tc = 1; tc <= TC; ++tc) {
		printf("Case #%d: ", tc);
		work();
	}
	
}