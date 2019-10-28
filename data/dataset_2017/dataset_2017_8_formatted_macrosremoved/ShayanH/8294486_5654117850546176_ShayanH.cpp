#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

const int MAXN = 1 * 1000 + 10;

pair<int, char> p[10];

int main() {
  ios::sync_with_stdio(false);

  int tt;
  cin >> tt;
  for (int tc = 1; tc <= tt; tc++) {
    cout << "Case #" << tc << ": ";

    int n, r, o, y, g, b, v;
    cin >> n >> r >> o >> y >> g >> b >> v;

    p[0] = make_pair(r, 'R');
    p[1] = make_pair(y, 'Y');
    p[2] = make_pair(b, 'B');
    sort(p, p + 3);

    if (p[2].first > n / 2) {
      cout << "IMPOSSIBLE" << endl;
    } else {
      string ans;
      for (int i = 0; i < n; i++)
        ans.push_back(' ');

      for (int c = 2; c >= 0; c--) {
        if (c % 2 == 0) {
          for (int i = 0; i < n; i++) {
            if (p[c].first == 0)
              break;

            int prev = (i - 1 + n) % n;
            if (ans[prev] != p[c].second && ans[i] == ' ') {
              ans[i] = p[c].second;
              p[c].first--;
            }
          }
        } else {
          for (int i = n - 1; i >= 0; i--) {
            if (p[c].first == 0)
              break;

            int next = (i + 1 + n) % n;
            if (ans[next] != p[c].second && ans[i] == ' ') {
              ans[i] = p[c].second;
              p[c].first--;
            }
          }
        }
      }
      for (int i = 0; i < n; i++)
        if (ans[i] == ' ')
          cerr << "BUG" << endl;

      cout << ans << endl;
    }
  }
  return 0;
}
