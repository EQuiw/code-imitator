#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <map>
#include <set>
#include <queue>
#define eps 1e-8
#define MAXN 100050
#define LL long long
using namespace std;
map<LL, LL> mp;
priority_queue<LL> q;
char s[15][15];
char ans[15][15];
int main() {
	freopen("A-small-attempt0 (1).in","r",stdin);
	freopen("A-small-attempt0 (1).out","w",stdout);
	int tt, ri = 0;
	scanf("%d", &tt);
	while (tt--) {
		int n, m;
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++i)
			scanf(" %s", s[i]);
		memset(ans, 0, sizeof(ans));
		for (int i = 0; i < n; ++i) {
			int now = 0;
			int flag = 0;
			for (int j = 0; j < m; ++j) {
				if (s[i][j] != '?')
					flag = 1;
			}
			if (flag == 0) {
				if (i != 0) {
					for (int j = 0; j < m; ++j)
						ans[i][j] = ans[i - 1][j];
				}
			} else {
//				puts("222");
				while (s[i][now] == '?') {
					now++;
				}
				for (int j = 0; j < now; ++j)
					ans[i][j] = s[i][now];
				while (now < m) {
					int p = now;
					while (p < m && (s[i][p] == s[i][now] || s[i][p] == '?')) {
						ans[i][p] = s[i][now];

//						printf("ip:%d %d %c %c\n",i,p,ans[i][p],s[i][now]);
						++p;
					}
//					printf("%d %d %s %c %c\n",i,p,ans[i],ans[i][0],ans[i][1]);
					now = p;
				}
			}
		}
//		for(int i=0;i<n;++i)
//					printf("%s\n",ans[i]);
		for (int i = n - 1; i >= 0; --i) {
			int flag = 0;
			for (int j = 0; j < m; ++j) {
				if (ans[i][j] != 0)
					flag = 1;
			}
			if (flag == 0) {
				if (i != n-1) {
					for (int j = 0; j < m; ++j)
						ans[i][j] = ans[i +1][j];
				}
			}
		}
		printf("Case #%d:\n",++ri);
		for(int i=0;i<n;++i)
			printf("%s\n",ans[i]);
	}
	return 0;
}
