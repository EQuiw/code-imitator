#include <bits/stdc++.h>
#define TR(c, it) for (__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define FOR(i, a, b) for (int i = (a), _b = (b); i < _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define FORE(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define SZ(c) (int)(c).size()

using namespace std;

const int N = 1010;

int a[6];
int ans[N];
string s = "ROYGBV";
int n;
int select(int prev) {
  int num = 0, pos = -1;
  for (int i = 0; i < 6; ++i)
    if (i != prev && a[i] > 0) {
      if (num < a[i]) {
        num = a[i];
        pos = i;
      }
    }
  return pos;
}
int main() {
  // freopen("A.inp", "r", stdin);
  // freopen("A.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int tests;
  cin >> tests;
  for (int test = 1; test <= tests; ++test) {
    cin >> n;
    for (int i = 0; i < 6; ++i)
      cin >> a[i];
    string ret = "";
    for (int i = 0; i < n; ++i) {
      if (i == 0) {
        ans[0] = select(-1);
      } else {
        ans[i] = select(ans[i - 1]);
      }
      if (ans[i] == -1) {
        ret = "IMPOSSIBLE";
      } else
        a[ans[i]]--;
    }
    if (ans[n - 1] == ans[0])
      ret = "IMPOSSIBLE";
    if (ret != "IMPOSSIBLE") {
      for (int i = 0; i < n; ++i)
        ret.push_back(s[ans[i]]);
    }
    cout << "Case #" << test << ": " << ret << endl;
  }
  return 0;
}
