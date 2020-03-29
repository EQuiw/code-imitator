//Problem C

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

const int trans[4][5] = {
	{0, 2, 0, 1, 3},
	{1, 1, 0, -1, -1},
	{2, 2, -1, 1, -1},
	{3, -1, 0, -1, 3}
};

char c[50][50];
bool dp[51][1024];
int choice[51][1024];
int nex[51][1024];

bool check(char c) {
	return c == '#' || c == '.' || c == '|' || c == '-' || c == '/' || c == '\\';
}

void deco(int mask, int *a) {
	for (int i = 0; i < 5; i++) {
		a[i] = mask & 3;
		mask >>= 2;
	}
}

int enco(int *a) {
	int ans = 0;
	for (int i = 0; i < 5; i++)
		ans |= (a[i] << (i * 2));
	return ans;
}

int main() {
	int totalTest = get();
	for (int test = 1; test <= totalTest; test++) {
		int R = get(), C = get();
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++) {
				while (c[i][j] = getchar(), !check(c[i][j]));
				if (c[i][j] == '|')
					c[i][j] = '-';
			}
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < 1024; i++) {
			int a[5];
			deco(i, a);
			bool flag = true;
			for (int j = 0; flag && j < 5; j++)
				flag = (a[j] != 2);
			dp[C][i] = flag;
		}
		for (int i = C - 1; i >= 0; i--) {
			int laser = 0;
			for (int j = 0; j < R; j++)
				if (c[j][i] == '|' || c[j][i] == '-')
					laser |= (1 << j);
			for (int mask = 0; mask < (1 << (R * 2)); mask++)
				for (int plan = 0; plan < (1 << R); plan++) {
					if ((laser & plan) != plan)
						continue;
					int a[5], b[5];
					deco(mask, a);
					for (int j = 0; j < R; j++)
						if (c[j][i] == '.')
							b[j] = 1;
						else if (c[j][i] == '#')
							b[j] = 2;
						else if (plan & (1 << j))
							b[j] = 4;
						else
							b[j] = 3;
					bool flag = true;
					for (int j = 0; flag && j < R; j++) {
						if (~plan & (1 << j))
							continue;
						int p = j;
						while (p > 0 && b[p - 1] == 1)
							b[--p] = 0;
						if (p > 0 && b[p - 1] >= 3)
							flag = false;
						p = j;
						while (p + 1 < R && b[p + 1] == 1)
							b[++p] = 0;
						if (p + 1 < R && b[p + 1] >= 3)
							flag = false;
					}
					for (int j = 0; flag && j < R; j++) {
						a[j] = trans[a[j]][b[j]];
						flag = (a[j] != -1);
					}
					if (flag) {
						int newmask = enco(a);
						if (dp[i + 1][newmask]) {
							dp[i][mask] = true;
							choice[i][mask] = plan;
							nex[i][mask] = newmask;
						}
					}
				}
		}
		printf("Case #%d: ", test);
		if (dp[0][0]) {
			printf("POSSIBLE\n");
			int cur = 0;
			for (int i = 0; i < C; i++) {
				for (int j = 0; j < R; j++)
					if (choice[i][cur] & (1 << j))
						c[j][i] = '|';
				cur = nex[i][cur];
			}
			for (int i = 0; i < R; i++) {
				for (int j = 0; j < C; j++)
					putchar(c[i][j]);
				putchar('\n');
			}
		}
		else
			printf("IMPOSSIBLE\n");
	}
	return 0;
}
