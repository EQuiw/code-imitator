#include <bits/stdc++.h>
using namespace std;

int t, n;

int c[6];
int g[3];
int ans[1234];
void work(int ca) {
  cin >> n;
  for (int i = 0; i < 6; i++)
    scanf("%d", &c[i]);
  g[0] = c[0];
  g[1] = c[2];
  g[2] = c[4];
  ans[0] = -1;
  // cout << g[0] << g[1] <<g[2]<<endl;
  printf("Case #%d: ", ca);
  for (int i = 1; i <= n; i++) {
    int mt = -1, mv;
    bool ok = 0;
    for (int j = 0; j < 3; j++)
      if (ans[i - 1] != j && mt <= g[j] && g[j] > 0) {
        ok = 1;
        if (mt == g[j] && j == ans[1]) {
          mv = j;
        }
        if (mt < g[j]) {
          mt = g[j];
          mv = j;
        }
      }
    if (!ok) {
      printf("IMPOSSIBLE\n");
      return;
    }
    ans[i] = mv;
    g[mv]--;
  }
  if (ans[1] == ans[n]) {
    printf("IMPOSSIBLE\n");
    return;
  }
  for (int i = 1; i <= n; i++) {
    if (ans[i] == 0)
      printf("R");
    if (ans[i] == 1)
      printf("Y");
    if (ans[i] == 2)
      printf("B");
  }
  printf("\n");
}
int main() {
  cin >> t;
  for (int _ = 1; _ <= t; _++)
    work(_);
  return 0;
}
