//Problem A

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

char a[25][25];

char getCake() {
	char c;
	while (c = getchar(), c != '?' && (c < 'A' || c > 'Z'));
	return c;
}

int main() {
	int totalTest = get();
	for (int test = 1; test <= totalTest; test++) {
		printf("Case #%d:\n", test);
		int n = get(), m = get();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				a[i][j] = getCake();
		
		for (int i = 0; i < n; i++) {
			for (int j = 1; j < m; j++)
				if (a[i][j] == '?' && a[i][j - 1] != '?')
					a[i][j] = a[i][j - 1];
			for (int j = m - 2; j >= 0; j--)
				if (a[i][j] == '?' && a[i][j + 1] != '?')
					a[i][j] = a[i][j + 1];
		}

		for (int i = 0; i < m; i++) {
			for (int j = 1; j < n; j++)
				if (a[j][i] == '?' && a[j - 1][i] != '?')
					a[j][i] = a[j - 1][i];
			for (int j = n - 2; j >= 0; j--)
				if (a[j][i] == '?' && a[j + 1][i] != '?')
					a[j][i] = a[j + 1][i];
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				putchar(a[i][j]);
			putchar('\n');
		}
	}
	return 0;
}
