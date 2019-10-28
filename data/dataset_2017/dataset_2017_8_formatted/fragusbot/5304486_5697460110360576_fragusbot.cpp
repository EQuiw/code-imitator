#include <bits/stdc++.h>

using namespace std;

const int inf = 1e8;
const int N = 77;

bool check_90(long long have, long long need) {
  return have * 100 >= 90 * need;
}

bool check_110(long long have, long long need) {
  return have * 100 <= 110 * need;
}

int get_l(int have, int need) {
  int l = 0, r = inf;
  while (r - l > 1) {
    int s = (l + r) / 2;
    if (check_90(have, 1LL * need * s)) {
      l = s;
    } else {
      r = s;
    }
  }
  return l;
}

int get_r(int have, int need) {
  int l = 0, r = inf;
  while (r - l > 1) {
    int s = (l + r) / 2;
    if (check_110(have, 1LL * need * s)) {
      r = s;
    } else {
      l = s;
    }
  }
  return r;
}

int need[N];
int have[N][N];
int p[N];

int main() {
  freopen("in", "r", stdin);
  freopen("out", "w", stdout);
  int tt;
  scanf("%d", &tt);
  for (int cc = 1; cc <= tt; ++cc) {
    double begt = clock();
    printf("Case #%d: ", cc);
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
      scanf("%d", need + i);
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        scanf("%d", have[i] + j);
      }
    }
    if (n == 1) {
      int ans = 0;
      for (int i = 0; i < m; ++i) {
        int l = get_l(have[0][i], need[0]);
        int r = get_r(have[0][i], need[0]);
        swap(l, r);
        if (l <= r) {
          ++ans;
        }
      }
      printf("%d\n", ans);
      continue;
    }
    for (int i = 0; i < m; ++i) {
      p[i] = i;
    }
    int ans = 0;
    do {
      int cur = 0;
      for (int i = 0; i < m; ++i) {
        int l0 = get_l(have[0][i], need[0]);
        int r0 = get_r(have[0][i], need[0]);
        swap(l0, r0);
        if (l0 > r0) {
          continue;
        }
        int l1 = get_l(have[1][p[i]], need[1]);
        int r1 = get_r(have[1][p[i]], need[1]);
        swap(l1, r1);
        if (l1 > r1) {
          continue;
        }
        int l = max(l0, l1);
        int r = min(r0, r1);
        if (l <= r) {
          ++cur;
        }
      }
      ans = max(ans, cur);
    } while (next_permutation(p, p + m));
    printf("%d\n", ans);
    fprintf(stderr, "case %d solved in %.3f\n", cc,
            (clock() - begt) / CLOCKS_PER_SEC);
  }
}