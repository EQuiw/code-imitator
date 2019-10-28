#include <bits/stdc++.h>
#define TR(c, it) for (__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define FOR(i, a, b) for (int i = (a), _b = (b); i < _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define FORE(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define SZ(c) (int)(c).size()

using namespace std;

const int N = 1010;

int n, k;
string s;

int main() {
  // freopen("A.inp", "r", stdin);
  // freopen("A.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int nTest;
  cin >> nTest;
  for (int test = 1; test <= nTest; ++test) {
    cin >> s >> k;
    n = SZ(s);
    int ans = 0;
    for (int i = 0; i <= n - k; ++i)
      if (s[i] == '-') {
        ans++;
        for (int j = i; j <= i + k - 1; ++j)
          if (s[j] == '-')
            s[j] = '+';
          else
            s[j] = '-';
      }
    bool happy = true;
    for (int i = 0; i < n; ++i)
      if (s[i] == '-') {
        happy = false;
        break;
      }
    cout << "Case #" << test << ": ";
    if (happy)
      cout << ans << endl;
    else
      cout << "IMPOSSIBLE" << endl;
  }
  return 0;
}
