#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int N, K;

int selected[1005], nmin[1005], nmax[1005];

void init() { memset(selected, 0, sizeof(selected)); }

pair<int, int> solve() {
  int cand, candmin, candmax;
  for (int i = 0; i < K; i++) {
    for (int j = 1; j <= N; j++) {
      if (selected[j] == 0) {
        int nl = 0;
        for (int k = j - 1; k >= 1; k--) {
          if (selected[k])
            break;
          nl++;
        }
        int nr = 0;
        for (int k = j + 1; k <= N; k++) {
          if (selected[k])
            break;
          nr++;
        }
        nmin[j] = min(nl, nr), nmax[j] = max(nl, nr);
      }
    }
    candmin = -1, candmax = -1;
    for (int j = 1; j <= N; j++) {
      if (selected[j])
        continue;
      if (nmin[j] > candmin)
        cand = j, candmin = nmin[j], candmax = nmax[j];
      else if (nmin[j] == candmin && nmax[j] > candmax)
        cand = j, candmin = nmin[j], candmax = nmax[j];
    }
    selected[cand] = 1;
  }
  return {nmax[cand], nmin[cand]};
}

int main() {
  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    init();
    scanf("%d%d", &N, &K);
    auto ans = solve();
    printf("Case #%d: %d %d\n", t, ans.first, ans.second);
  }
  return 0;
}
