#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;


char ch[] = {'R', 'O', 'Y', 'G', 'B', 'V'};
int b[1111], a[10];
int n;

bool check(int x, int y) {
	if (x > y) swap(x, y);
	return (x == y) || (x + 1 == y) || ((x&1) && (x+2 == y));
}

bool solve() {
	memset(b, -1, sizeof(b));
	for (int i = 0; i < n; ++i) {
		if (a[1]) {
			if (a[4]) {
				if (i > 0 && check(b[i-1], 4)) {
					int x = (b[i-1] + 3) % 6;
					if (a[x]) {
						b[i] = x;
						i++;
						a[x]--;
					} else return false;
				}
				b[i] = 4, b[i+1] = 1;
				a[1]--, a[4]--;
				//printf("%d %d\n", a[1], a[4]);
				++i;
			} else {
				return false;
			}
		} else if (a[3]) {
			if (a[0]) {
				if (i > 0 && check(b[i-1], 0)) {
					int x = (b[i-1] + 3) % 6;
					if (a[x]) {
						b[i] = x;
						i++;
						a[x]--;
					} else return false;
				}
				b[i] = 0, b[i+1] = 3;
				++i;
				a[3]--, a[0]--;
			} else return false;
		} else if (a[5]) {
			if (a[2]) {
				if (i > 0 && check(b[i-1], 2)) {
					int x = (b[i-1] + 3) % 6;
					if (a[x]) {
						b[i] = a[x];
						i++;
						a[x]--;
					} else return false;
				}
				b[i] = 2, b[i+1] = 5;
				++i;
				a[2]--, a[5]--;
			} else return false;
		} else {
			//printf("i=%d\n", i);
			if (i == 0) {
				if (a[0]) b[0] = 0, a[0]--;
				else if (a[2]) b[0] = 2, a[2]--;
				else if (a[4]) b[0] = 4, a[4]--;
			} else {
				int x = -1, mx = 0;
				for (int j = 0; j < 6; j += 2) {
					if (a[j] && !check(b[i-1], j)) {
						if (a[j] > mx) {
							mx = a[j], x = j;
						}
					}
				}
				if (x == -1) return false;
				a[x]--, b[i] = x;
			}
			//printf("bi=%d\n", b[i]);
			if (b[i] == -1) return false;
		}
	}
	return !check(b[0], b[n-1]);
	return true;
}


void work() {

	scanf("%d", &n);
	for (int i = 0; i < 6; ++i) {
		scanf("%d", &a[i]);
	}
	if (!solve()) printf("IMPOSSIBLE\n");
	else {
		for (int i = 0; i < n; ++i) {
			printf("%c", ch[b[i]]);
		}
		printf("\n");
	}

}

int main() {
	freopen("B-small-attempt1.in", "r", stdin);
	freopen("B-small-attempt1.out", "w", stdout);
	int TC;
	scanf("%d", &TC);
	for (int tc = 1; tc <= TC; ++tc) {
		printf("Case #%d: ", tc);
		work();
	}
	
}