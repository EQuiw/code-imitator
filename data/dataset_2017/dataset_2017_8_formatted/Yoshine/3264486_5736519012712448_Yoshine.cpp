#include <bits/stdc++.h>

using namespace std;

int t, k;
char s[1234];
int c[1234], n;

inline int lowbit(int x) { return x & (-x); }

inline void updata(int x, int y) {
  for (int i = x; i > 0; i -= lowbit(i))
    c[i] += y;
}

inline int query(int x) {
  int r = 0;
  for (int k = x; k <= n; k += lowbit(k)) {
    r += c[k];
  }
  return r;
}

void work(int ca) {
  int ans = 0;
  scanf("%s %d", s, &k);
  memset(c, 0, sizeof(c));
  n = strlen(s);
  for (int i = 0; i < n - k + 1; i++) {
    if (s[i] == '+') {
      if (query(i + 1) % 2 == 1) {
        ans += 1;
        updata(i + k, 1);
        updata(i, -1);
      }
    } else {
      if (query(i + 1) % 2 == 0) {
        ans += 1;
        updata(i + k, 1);
        updata(i, -1);
      }
    }
  }
  bool ok = 1;
  for (int i = n - k + 1; i < n; i++) {
    if ((s[i] == '+') && (query(i + 1) % 2 == 1)) {
      ok = 0;
      break;
    }
    if ((s[i] == '-') && (query(i + 1) % 2 == 0)) {
      ok = 0;
      break;
    }
  }
  printf("Case #%d: ", ca);
  if (ok)
    printf("%d\n", ans);
  else
    printf("IMPOSSIBLE\n");
}

int main() {
  scanf("%d", &t);
  for (int cas = 1; cas <= t; cas++)
    work(cas);
  return 0;
}
