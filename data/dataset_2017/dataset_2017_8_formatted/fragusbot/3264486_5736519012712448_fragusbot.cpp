#include <bits/stdc++.h>

using namespace std;

char s[77];
int q[7777];
int d[7777];

int main() {
  freopen("in", "r", stdin);
  freopen("out", "w", stdout);
  int tt;
  scanf("%d", &tt);
  for (int cc = 1; cc <= tt; ++cc) {
    printf("Case #%d: ", cc);
    int k;
    scanf("%s %d", s, &k);
    int n = strlen(s);
    q[0] = 1 << n;
    for (int i = 0; i < n; ++i) {
      if (s[i] == '-') {
        q[0] |= 1 << (n - 1 - i);
      }
    }
    memset(d, -1, sizeof d);
    d[q[0]] = 0;
    for (int qh = 0, qt = 1; qh < qt; ++qh) {
      int x = q[qh];
      for (int i = 0; i <= n - k; ++i) {
        int nx = x ^ (((1 << k) - 1) << i);
        if (d[nx] == -1) {
          d[nx] = d[x] + 1;
          q[qt++] = nx;
        }
      }
    }
    if (d[1 << n] == -1) {
      puts("IMPOSSIBLE");
    } else {
      printf("%d\n", d[1 << n]);
    }
  }
}