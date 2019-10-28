#include <bits/stdc++.h>

using namespace std;

//#define LARGE

struct Color {
  char c;
  int x;

  bool operator<(const Color &other) const { return x < other.x; }
} color[10];

int n, r, o, y, g, b, v;
int ans[1005];

int main() {

  freopen("B-small.in", "r", stdin);
  freopen("B-small.out", "w", stdout);

  int T;
  scanf("%d", &T);
  for (int Case = 1; Case <= T; ++Case) {
    scanf("%d %d %d %d %d %d %d", &n, &r, &o, &y, &g, &b, &v);
    printf("Case #%d: ", Case);
    color[0].x = r;
    color[0].c = 'R';
    color[1].x = y;
    color[1].c = 'Y';
    color[2].x = b;
    color[2].c = 'B';
    sort(color, color + 3);
    if (n / 2 < color[2].x) {
      printf("IMPOSSIBLE\n");
      continue;
    }
    memset(ans, -1, sizeof(ans));
    for (int i = 0; i < color[2].x; ++i)
      ans[i << 1] = 2;
    for (int i = 0; i < color[1].x; ++i)
      ans[n - (i << 1) - (n & 1) - 1] = 1;
    for (int i = 0; i < n; ++i)
      if (ans[i] == -1)
        ans[i] = 0;
    for (int i = 0; i < n; ++i)
      printf("%c", color[ans[i]].c);
    printf("\n");
  }
  return 0;
}
