#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pt;
const int base = 1000000007;
const int maxn = 102;

int n, m;
char a[maxn][maxn];
int f[maxn][maxn][255];
bool b[102][102];

int sum(int first, int second, int u, int v, char k) {
  return f[u][v][k] - f[u][second - 1][k] - f[first - 1][v][k] +
         f[first - 1][second - 1][k];
}

void solve(int test) {
  int i, j, k, v, L, R;
  char h;

  scanf("%d%d\n", &m, &n);
  for (i = 1; i <= m; i++) {
    for (j = 1; j <= n; j++) {
      scanf("%c", &a[i][j]);
      b[i][j] = false;
      if (a[i][j] != '?')
        b[i][j] = true;
    }
    scanf("\n");
  }

  for (i = 0; i <= m; i++)
    for (j = 0; j <= n; j++)
      for (k = 'A'; k <= 'Z'; k++)
        f[i][j][k] = 0;

  for (i = 1; i <= m; i++)
    for (j = 1; j <= n; j++)
      if (b[i][j]) {
        h = a[i][j];
        for (k = j - 1; k >= 0; k--) {
          if (a[i][k] != '?') {
            L = k + 1;
            break;
          }
          a[i][k] = h;
        }
        for (k = j + 1; k <= n + 1; k++) {
          if (a[i][k] != '?') {
            R = k - 1;
            break;
          }
          a[i][k] = h;
        }

        for (k = i - 1; k >= 1; k--) {
          bool expand = true;
          for (v = L; v <= R; v++)
            if (a[k][v] != '?' && a[k][v] != h) {
              expand = false;
              break;
            }
          if (expand)
            for (v = L; v <= R; v++)
              a[k][v] = h;
          else
            break;
        }
        for (k = i + 1; k <= m; k++) {
          bool expand = true;
          for (v = L; v <= R; v++)
            if (a[k][v] != '?' && a[k][v] != h) {
              expand = false;
              break;
            }
          if (expand)
            for (v = L; v <= R; v++)
              a[k][v] = h;
          else
            break;
        }
      }

  printf("Case #%d:\n", test);
  for (i = 1; i <= m; i++) {
    for (j = 1; j <= n; j++)
      printf("%c", a[i][j]);
    printf("\n");
  }
}

int main() {
  int i, t;
  freopen("A11.in", "r", stdin);
  freopen("A1.out", "w", stdout);

  scanf("%d", &t);
  for (i = 1; i <= t; i++)
    solve(i);

  return 0;
}
