//Problem B

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<set>

using namespace std;

int get() {
	char c;
	while (c = getchar(), c != '-' && (c < '0' || c > '9'));
	bool flag = (c == '-');
	if (flag)
		c = getchar();
	int x = 0;
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return flag ? -x : x;
}

const int MAXN = 1000;

int a[MAXN][MAXN];
vector<int> g[MAXN];
int x[MAXN], y[MAXN], peer[MAXN];
bool flag[MAXN];

bool dfs(int x) {
	if (x == -1)
		return true;
	if (flag[x])
		return false;
	flag[x] = true;
	for (int i = 0; i < g[x].size(); i++) {
		int y = peer[g[x][i]];
		if (dfs(y)) {
			peer[g[x][i]] = x;
			return true;
		}
	}
	return false;
}

int main() {
	int totalTest = get();
	for (int test = 1; test <= totalTest; test++) {
		int n = get(), m = get(), e = get();
		memset(a, 0, sizeof(a));
		for (int i = 0; i < e; i++) {
			int x = get() - 1, y = get() - 1;
			a[x][y]++;
		}
		int s = 0, t = 0;
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < a[i][0]; j++)
				x[s++] = i;
			for (int j = 0; j < a[i][1]; j++)
				y[t++] = i;
		}
		for (int i = 0; i < s; i++) {
			g[i].clear();
			for (int j = 0; j < t; j++)
				if (x[i] != y[j])
					g[i].push_back(j);
		}
		memset(peer, -1, sizeof(peer));
		int match = 0;
		for (int i = 0; i < s; i++) {
			memset(flag, 0, sizeof(flag));
			if (dfs(i))
				match++;
		}
		s = max(s - a[0][1], 0);
		t = max(t - a[0][0], 0);
		int ans = a[0][0] + a[0][1] + max(s, t);
		int need = 0;
		if (match < min(s, t))
			need = min(s, t) - match;
		printf("Case #%d: %d %d\n", test, ans, need);
	}
	return 0;
}
