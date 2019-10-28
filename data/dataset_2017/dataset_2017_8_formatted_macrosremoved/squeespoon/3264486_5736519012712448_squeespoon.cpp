#include <bits/stdc++.h>

using namespace std;

char s[1010];

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-small-attempt0.out", "w", stdout);
  int t;
  cin >> t;
  int cas = 0;
  while (t--) {
    cas++;

    scanf("%s", s);
    int k;
    cin >> k;

    int n = strlen(s);

    int ans = 0;
    for (int i = 0; i <= n - k; i++) {
      if (s[i] == '+') {
      } else {
        ans++;
        for (int j = 0; j < k; j++) {
          if (s[i + j] == '+') {
            s[i + j] = '-';
          } else {
            s[i + j] = '+';
          }
        }
      }
    }

    bool ok = 1;
    for (int i = 0; i < n; i++) {
      if (s[i] == '-') {
        ok = 0;
      }
    }

    printf("Case #%d: ", cas);
    if (ok) {
      cout << ans << endl;
    } else {
      cout << "IMPOSSIBLE" << endl;
    }
  }

  return 0;
}
