#include <stdio.h>
#include <algorithm>
using namespace std;

int T, cas;
int N;
int R, O, Y, G, B, V;
char first;

void dfs(int r, int y, int b, char prefix)
{
	if (r == 0 && y == 0 && b == 0)
		return;
	if (prefix == 'R') {
		if (y > b) {
			printf("Y");
			dfs(r, y-1, b, 'Y');
		} else if (y < b) {
			printf("B");
			dfs(r, y, b-1, 'B');
		} else {
			if (first == 'Y') {
				printf("Y");
				dfs(r, y-1, b, 'Y');
			} else {
				printf("B");
				dfs(r, y, b-1, 'B');
			}
		}
	} else if (prefix == 'Y') {
		if (r > b) {
			printf("R");
			dfs(r-1, y, b, 'R');
		} else if (r < b) {
			printf("B");
			dfs(r, y, b-1, 'B');
		} else {
			if (first == 'R') {
				printf("R");
				dfs(r-1, y, b, 'R');
			} else {
				printf("B");
				dfs(r, y, b-1, 'B');
			}
		}
	} else if (prefix == 'B') {
		if (r > y) {
			printf("R");
			dfs(r-1, y, b, 'R');
		} else if (r < y) {
			printf("Y");
			dfs(r, y-1, b, 'Y');
		} else {
			if (first == 'R') {
				printf("R");
				dfs(r-1, y, b, 'R');
			} else {
				printf("Y");
				dfs(r, y-1, b, 'Y');
			}
		}
	} else {
		if (r > y && r > b) {
			first = 'R';
			printf("R");
			dfs(r-1, y, b, 'R');
		} else if (y >= r && y > b) {
			first = 'Y';
			printf("Y");
			dfs(r, y-1, b, 'Y');
		} else {
			first = 'B';
			printf("B");
			dfs(r, y, b-1, 'B');
		}
	}
}

void solve()
{
	if (R > Y+B) {
		printf("IMPOSSIBLE");
		return;
	}

	if (Y > R+B) {
		printf("IMPOSSIBLE");
		return;
	}

	if (B > R+Y) {
		printf("IMPOSSIBLE");
		return;
	}

	dfs(R, Y, B, 'x');
}

int main()
{
	scanf(" %d", &T);
	for (cas = 1; cas <= T; cas++) {
		scanf(" %d %d %d %d %d %d %d", &N, &R, &O, &Y, &G, &B, &V);

		printf("Case #%d: ", cas);
		solve();
		puts("");
	}

	return 0;
}