#include <bits/stdc++.h>

using namespace std;

pair<int, int> a[3];
int z[1010];

int main() {
  freopen("in", "r", stdin);
  freopen("out", "w", stdout);
  int tt;
  scanf("%d", &tt);
  for (int cc = 1; cc <= tt; ++cc) {
    double begt = clock();
    printf("Case #%d: ", cc);
    int n, R, O, Y, G, B, V;
    scanf("%d %d %d %d %d %d %d", &n, &R, &O, &Y, &G, &B, &V);
    a[0] = {R, 0};
    a[1] = {Y, 1};
    a[2] = {B, 2};
    sort(a, a + 3);
    memset(z, -1, sizeof z);
    for (int i = 2; i >= 0; --i) {
      while (a[i].first > 0) {
        int pos = -1;
        for (int j = 0; j < n; j += 2) {
          if (z[j] == -1) {
            pos = j;
            break;
          }
        }
        if (pos != -1) {
          z[pos] = a[i].second;
          --a[i].first;
          continue;
        }
        for (int j = 1; j < n; j += 2) {
          if (z[j] == -1) {
            pos = j;
            break;
          }
        }
        z[pos] = a[i].second;
        --a[i].first;
      }
    }
    bool can = true;
    for (int i = 0; i < n; ++i) {
      if (z[i] == z[(i + 1) % n]) {
        can = false;
      }
    }
    if (!can) {
      puts("IMPOSSIBLE");
    } else {
      for (int i = 0; i < n; ++i) {
        if (z[i] == 0) {
          putchar('R');
        } else if (z[i] == 1) {
          putchar('Y');
        } else {
          putchar('B');
        }
      }
      putchar('\n');
    }
    fprintf(stderr, "case %d solved in %.3f\n", cc,
            (clock() - begt) / CLOCKS_PER_SEC);
  }
}