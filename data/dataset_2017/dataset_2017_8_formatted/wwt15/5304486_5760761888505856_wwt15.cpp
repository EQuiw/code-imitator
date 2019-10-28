#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
#define eprintf(...) fprintf(stderr, __VA_ARGS__)

const int N = 30;

int n, m;
char s[N][N];

bool check(int y, int l, int r) {
  for (int i = l; i <= r; i++)
    if (s[i][y] != '?')
      return false;
  return true;
}

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A.out", "w", stdout);
  int T;
  scanf("%d", &T);
  for (int Case = 1; Case <= T; Case++) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
      scanf("%s", s[i] + 1);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++)
        if (s[i][j] != '?') {
          int t = i - 1;
          while (t >= 1 && s[t][j] == '?')
            t--;
          t++;
          int l = j - 1;
          while (l >= 1 && check(l, t, i))
            l--;
          l++;
          int r = j + 1;
          while (r <= m && check(r, t, i))
            r++;
          r--;
          for (int x = t; x <= i; x++)
            for (int y = l; y <= r; y++)
              s[x][y] = s[i][j];
        }
    }
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
        if (s[i][j] == '?')
          s[i][j] = s[i - 1][j];
    printf("Case #%d:\n", Case);
    for (int i = 1; i <= n; i++)
      puts(s[i] + 1);
  }
}
