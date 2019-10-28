#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1010;

char w[N];
int sa[N];

int main() {
  int T;
  scanf("%d", &T);

  for (int t = 1; t <= T; t++) {
    int n, k;
    scanf(" %s %d", w, &k);
    n = strlen(w);

    for (int i = 0; i < n; i++)
      sa[i] = 0;

    int ans = 0, cur = 0;
    for (int i = 0; i + k <= n; i++) {
      cur -= sa[i];

      int b = w[i] == '+';
      b ^= (cur & 1);

      if (!b) {
        ans++;
        cur++;
        sa[i + k] += 1;
      }
    }

    bool ok = true;
    for (int i = n - k + 1; i < n; i++) {
      cur -= sa[i];

      int b = w[i] == '+';
      b ^= (cur & 1);

      ok = ok && (b == 1);
    }

    if (!ok)
      printf("Case #%d: IMPOSSIBLE\n", t);
    else
      printf("Case #%d: %d\n", t, ans);
  }

  return 0;
}
