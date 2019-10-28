#include <bits/stdc++.h>
using namespace std;
const int N = 100 + 5;
typedef long long LL;
int T, Case, n, q;
int d[N][N], E[N], S[N];
LL X[N];
double f[N];

int main() {
    freopen("C-small-attempt0.in", "r", stdin);
    freopen("out0.out", "w", stdout);
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &q);
        for(int i = 1; i <= n; i++) {
            scanf("%d%d", &E[i], &S[i]);
        }
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                scanf("%d", &d[i][j]);
            }
        }
        for(int i = 2; i <= n; i++) {
            X[i] = X[i-1] + d[i-1][i];
            f[i] = 1e100;
        }
        printf("Case #%d:", ++Case);
        f[1] = 0;
        while(q--) {
            int u, v;
            scanf("%d%d", &u, &v);
            for(int i = 2; i <= n; i++) {
                for(int j = 1; j < i; j++) {
                    if(X[i] - X[j] <= E[j] + 1e-8) {
                        f[i] = min(f[i], f[j] + 1.0*(X[i] - X[j])/S[j]);
                    }
                }
            }
            printf(" %.10f", f[n]);
        }
        puts("");
    }
    return 0;
}
