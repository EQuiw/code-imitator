#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

int mt[][3] = {{0, 1, 2},
{0, 2, 0},
{0, 3, 2},
{1, 0, 1},
{1, 1, 3},
{1, 2, 1},
{1, 3, 3},
{2, 0, 2},
{2, 1, 0},
{2, 2, 2},
{2, 3, 0},
{3, 0, 3},
{3, 1, 1},
{3, 2, 3},
{3, 3, 1}};
int m = 15;
int f[111][111], g[111][111][111];
int n, p, a[111], ans;

void work() {
    scanf("%d%d", &n, &p);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    ans = 0;
    if (p == 2) {
        for (int i = 0; i < n; ++i) {
            ans += a[i] & 1;
        }
        printf("%d\n", n - ans + (ans+1)/2);
    } else if (p == 3) {
        int x1, x2;
        x1 = x2 = 0;
        for (int i = 0; i < n; ++i) {
            x1 += (a[i] % 3) == 1;
            x2 += (a[i] % 3) == 2;
        }
        memset(f, 0, sizeof(f));
        for (int i = 0; i <= x1; ++i) {
            for (int j = 0; j <= x2; ++j) {
                if (i - 1 >= 0 && j - 1 >= 0) f[i][j] = max(f[i][j], f[i-1][j-1] + 1);
                if (i - 3 >= 0) f[i][j] = max(f[i][j], f[i-3][j] + 1);
                if (j - 3 >= 0) f[i][j] = max(f[i][j], f[i][j-3] + 1);
            }
        }
        ans = f[x1][x2];
        if (x1 > 0) ans = max(f[x1-1][x2] + 1, ans);
        if (x2 > 0) ans = max(f[x1][x2-1] + 1, ans);
        printf("%d\n", ans + n - x1 - x2);
    } else {
        int x1, x2, x3;
        x1 = x2 = x3 = 0;
        memset(g, 0, sizeof(g));
        for (int i = 0; i <= x1; ++i) {
            for (int j = 0; j <= x2; ++j) {
                for (int k = 0; k <= x3; ++k) {
                    for (int o = 0; o < m; ++o) {
                        if (i - mt[o][0] >= 0 && j - mt[o][1] >= 0 && k - mt[o][2] >= 0) g[i][j][k] = max(g[i][j][k], g[i-mt[o][0]][j-mt[o][1]][k-mt[o][2]] + 1);
                    }
                    if (i - 4 >= 0) g[i][j][k] = max(g[i][j][k], g[i-4][j][k] + 1);
                    if (j - 4 >= 0) g[i][j][k] = max(g[i][j][k], g[i][j-4][k] + 1);
                    if (k - 4 >= 0) g[i][j][k] = max(g[i][j][k], g[i][j][k-4] + 1);
                }
            }
        }
        ans = g[x1][x2][x3];
        if (x1 > 0) ans = max(g[x1-1][x2][x3] + 1, ans);
        if (x2 > 0) ans = max(g[x1][x2-1][x3] + 1, ans);
        if (x3 > 0) ans = max(g[x1][x2][x3-1] + 1, ans);
        printf("%d\n", g[x1][x2][x3] + n - x1 - x2 - x3);
    }
}

int main() {
    freopen("A-small-attempt0.in", "r", stdin);
    freopen("A-small-attempt0.out", "w", stdout);
    int TC;
    scanf("%d", &TC);
    for (int tc = 1; tc <= TC; ++tc) {
        printf("Case #%d: ", tc);
        work();
    }
    
}