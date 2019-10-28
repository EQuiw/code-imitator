#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

int r, c;
char G[26][26];

void exp(int r, int c, char G[26][26]) {
    int rl[26], rr[26], cl[26], cr[26];
    for (int i = 0; i < 26; ++i) {
        rl[i] = r;
        rr[i] = -1;
        cl[i] = c;
        cr[i] = -1;
    }
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (G[i][j] != '?') {
                int x = G[i][j] - 'A';
                rl[x] = min(rl[x], i);
                rr[x] = max(rr[x], i);
                cl[x] = min(cl[x], j);
                cr[x] = max(cr[x], j);
            }
        }
    }
    for (int i = 0; i < 26; ++i) {
        for (int p = rl[i]; p <= rr[i]; ++p) {
            for (int q = cl[i]; q <= cr[i]; ++q) {
                G[p][q] = 'A' + i;
            }
        }
    }
}
void push(int r, int c, char G[26][26]) {
    bool vis[26];
    memset(vis, 0x00, sizeof(vis));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (G[i][j] != '?' && !vis[G[i][j] - 'A']) {
                vis[G[i][j] - 'A'] = true;

                int p, q;
                for (p = i; p < r && G[p][j] == G[i][j]; ++p) {}
                --p;
                for (q = j; q < c && G[i][q] == G[i][j]; ++q) {}
                --q;

                for (int x = p + 1; x < r; ++x) {
                    bool flag = true;
                    for (int y = j; y <= q; ++y) {
                        if (G[x][y] != '?') {
                            flag = false;
                            break;
                        }
                    }
                    if (flag) {
                        for (int y = j; y <= q; ++y) {
                            G[x][y] = G[i][j];
                        }
                    } else {
                        break;
                    }
                }

            }

        }
    }
}
void rot(int& r, int& c, char G[26][26]) {
    char tG[26][26];
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            // 0,0->0,r-1
            // r-1,0->0,0
            // 0,c-1->c-1,r-1
            // r-1,c-1->c-1,0
            tG[j][r - 1 - i] = G[i][j];
        }
    }
    swap(r, c);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            G[i][j] = tG[i][j];
        }
    }
}

int main() {
    freopen("A-small-attempt0.in", "r", stdin);
    freopen("A-small-attempt0.out", "w", stdout);

    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++test) {
        scanf("%d%d", &r, &c);
        for (int i = 0; i < r; ++i) {
            scanf("%s", G[i]);
        }
        exp(r, c, G);
        for (int i = 0; i < 4; ++i) {
            push(r, c, G);
            rot(r, c, G);
        }
        printf("Case #%d:\n", test);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                printf("%c", G[i][j]);
            }
            puts("");
        }
    }

    return 0;
}
