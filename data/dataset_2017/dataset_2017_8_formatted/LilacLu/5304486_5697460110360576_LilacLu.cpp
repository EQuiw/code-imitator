#include <bits/stdc++.h>

using namespace std;

#define SMALL
//#define LARGE

struct Range {
  int l, r;
  vector<int> belong;
};

int n, p;
int ns[55], ps[55][55];
bool used[55][55];

int main() {
#ifdef SMALL
  freopen("B-small.in", "r", stdin);
  freopen("B-small.out", "w", stdout);
#endif
#ifdef LARGE
  freopen("B-large.in", "r", stdin);
  freopen("B-large.out", "w", stdout);
#endif
  int T;
  scanf("%d", &T);
  for (int Case = 1; Case <= T; ++Case) {
    scanf("%d %d", &n, &p);
    for (int i = 0; i < n; ++i)
      scanf("%d", &ns[i]);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < p; ++j)
        scanf("%d", &ps[i][j]);
      sort(ps[i], ps[i] + p);
    }
    memset(used, false, sizeof(used));
    int ans = 0;
    for (int i = 0; i < p; ++i) {
      vector<Range> now, _now;
      Range t;
      t.l = 0;
      t.r = (int)1e7;
      now.push_back(t);
      for (int j = 0; j < n; ++j) {
        _now.clear();
        for (int k = 0; k < p; ++k) {
          if (used[j][k])
            continue;
          int l = ceil(ps[j][k] / (1.1 * ns[j]));
          int r = floor(ps[j][k] / (0.9 * ns[j]));
          //          printf("%d %d %d %d\n", j, k, l, r);
          if (l > r)
            continue;
          for (int s = 0; s < now.size(); ++s) {
            Range temp = now[s];
            //            printf("%d %d, ", temp.l, temp.r);
            if (temp.l > r || temp.r < l)
              continue;
            temp.l = max(temp.l, l);
            temp.r = min(temp.r, r);
            temp.belong.push_back(k);
            _now.push_back(temp);
          }
          //          printf("\n");
        }
        now = _now;
        if (now.size() == 0)
          break;
      }
      if (now.size() == 0)
        continue;
      t = now[0];
      assert(t.belong.size() == n);
      for (int i = 0; i < t.belong.size(); ++i)
        used[i][t.belong[i]] = true;
      ++ans;
    }
    printf("Case #%d: %d\n", Case, ans);
  }
  return 0;
}
