#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>

using namespace std;

#define N 30
#define DEBUG 0

char f[N][N];
int n, m;

int main() {
    if (!DEBUG) {
        freopen("in", "r", stdin);
        freopen("out", "w", stdout);
    }
    int t, T = 1;

    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++i) {
            scanf("%s", f[i]);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (f[i][j] != '?') {
                    for (int k = j - 1; k >= 0; --k) {
                        if (f[i][k] == '?') {
                            f[i][k] = f[i][j];
                        } else {
                            break;
                        }
                    }
                    for (int k = j + 1; k < m; ++k) {
                        if (f[i][k] == '?') {
                            f[i][k] = f[i][j];
                        } else {
                            break;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (f[i][0] != '?') {
                for (int k = i - 1; k >= 0; --k) {
                    if (f[k][0] == '?') {
                        for (int j = 0; j < m; ++j) {
                            f[k][j] = f[i][j];
                        }
                    } else {
                        break;
                    }
                }
                for (int k = i + 1; k < n; ++k) {
                    if (f[k][0] == '?') {
                        for (int j = 0; j < m; ++j) {
                            f[k][j] = f[i][j];
                        }
                    } else {
                        break;
                    }
                }
            }
        }
        printf("Case #%d:\n", T++);
        for (int i = 0; i < n; ++i) {
            printf("%s\n", f[i]);
        }
    }
    return 0;
}