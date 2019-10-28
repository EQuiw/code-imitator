#include <bits/stdc++.h>

using namespace std;

int main() {

  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-small-attempt0.out", "w", stdout);

  int t;
  cin >> t;
  int cas = 0;

  while (t--) {
    cas++;
    double len;
    int n;
    cin >> len >> n;

    double time = 0;

    for (int i = 1; i <= n; i++) {
      double k, s;
      cin >> k >> s;

      time = max(time, (len - k) / s);
    }

    double v = len / time;
    printf("Case #%d: %.6f\n", cas, v);
  }
  return 0;
}
