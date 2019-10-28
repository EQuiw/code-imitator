/******************************************
*    AUTHOR:         BHUVNESH JAIN        *
*    INSTITUITION:   BITS PILANI, PILANI  *
******************************************/
#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL; 
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL, LL> pll;

const int MAX = 51;

int r[MAX];
int q[MAX][MAX];

bool chk(LL a, LL b, LL c) {
	if (b >= 0) {
		// printf("%lld %lld %lld\n", a, b, c);
		LL x = a * b;
		LL u = (10 * c) / 9;
		LL v = (10 * c + 10) / 11;
		assert(((9*c)/10) <= u);
		assert(((11*c)/10) >= v);
		return (v <= x && x <= u);
	}
	else {
		return false;
	}
}

int main() {
	int t;
	scanf("%d", &t);
	for(int T = 1; T <= t; ++T) {
		printf("Case #%d: ", T);
		int n, p;
		scanf("%d %d", &n, &p);
		for(int i = 0; i < n; ++i) {
			scanf("%d", &r[i]);
		}
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < p; ++j) {
				scanf("%d", &q[i][j]);
			}
		}
		int ans = 0;
		if (n == 1) {
			for(int j = 0; j < p; ++j) {
				int u = q[0][j]/r[0];
				if (chk(r[0], u-1, q[0][j])) {
					ans += 1;
				}
				else if (chk(r[0], u, q[0][j])) {
					ans += 1;
				}
				else if (chk(r[0], u+1, q[0][j])) {
					ans += 1;
				}
			}
		}
		else if (n == 2) {
			vector<int> perm(p);
			for(int i = 0; i < p; ++i) {
				perm[i] = i;
			}
			do {
				int val = 0;
				for(int j = 0; j < p; ++j) {
					int u = q[0][j] / r[0];
					int v = q[1][perm[j]] / r[1];
					// printf("%d %d\n", u, v);
					for(int X = min(u,v)-1; X <= max(u,v)+1; ++X) {
						if (chk(r[0], X, q[0][j]) && chk(r[1], X, q[1][perm[j]])) {
							val += 1;
							break;
						}
					}
				}
				ans = max(ans, val);
			}while(next_permutation(perm.begin(), perm.end()));
		}
		printf("%d\n", ans);
	}
	return 0;
}