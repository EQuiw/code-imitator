#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

#define N 60
#define DEBUG 0
#define inf 2147483640

int a[N], it[N];
int n, m, ans;

struct seg {
  int s, e;

  bool operator<(const seg ff) const { return e < ff.e; }
} f[N][N];

bool yes() {
  int mn = inf, mx = 0;
  for (int i = 0; i < n; ++i) {
    mn = min(mn, f[i][it[i]].e);
    mx = max(mx, f[i][it[i]].s);
  }
  //    printf("mx %d mn %d \n", mx, mn);
  return mn >= mx;
}

bool out() {
  for (int i = 0; i < n; ++i) {
    if (it[i] == m) {
      return true;
    }
  }
  return false;
}

int main() {
  if (!DEBUG) {
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
  }
  int t, T = 1;

  scanf("%d", &t);
  while (t--) {
    ans = 0;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        int d;
        scanf("%d", &d);
        int s = (int)floor(10.0 * d / 11 / a[i]);
        if (s * a[i] * 11 < d * 10) {
          ++s;
        }
        int e = (int)ceil(10.0 * d / 9 / a[i]);
        if (e * a[i] * 9 > d * 10) {
          --e;
        }
        if (s > e) {
          s = e = 0;
        }
        f[i][j].s = s;
        f[i][j].e = e;
        //                printf("%d %d\n", s, e);
      }
      sort(f[i], f[i] + m);
    }
    memset(it, 0, sizeof(it));
    for (int i = 0; i < n; ++i) {
      while (it[i] < m && f[i][it[i]].e == 0) {
        ++it[i];
      }
    }

    //        for (int i = 0; i < n; ++i) {
    //            for (int j = 0; j < m; ++j) {
    //                printf(" ( %d , %d ) ", f[i][j].s, f[i][j].e);
    //            }
    //            printf("\n");
    //        }
    while (!out()) {
      if (yes()) {
        ++ans;
        for (int i = 0; i < n; ++i) {
          //                    printf("%d ", it[i]);
          ++it[i];
        }
        //                printf("\n");
      } else {
        int mn = inf;
        for (int i = 0; i < n; ++i) {
          mn = min(mn, f[i][it[i]].e);
        }
        for (int i = 0; i < n; ++i) {
          if (f[i][it[i]].e == mn) {
            //                        printf("i %d ( %d, %d)\n", i,
            //                        f[i][it[i]].s, f[i][it[i]].e);
            ++it[i];
          }
        }
      }
    }
    printf("Case #%d: %d\n", T++, ans);
  }
  return 0;
}