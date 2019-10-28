#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<pii, int> para;
const int inf = 1e9 + 7;
const int maxN = 1e6 + 5;

int t, k;
string s;

int main() {
  ios_base::sync_with_stdio(0);
  cin >> t;
  for (int x = (1); x <= ((t)); ++x) {
    cin >> s >> k;
    int ans = 0;
    for (int i = (0); i <= (((int)s.size() - k + 1) - 1); ++i) {
      if (s[i] == '-') {
        for (int j = (i); j <= (i + k - 1); ++j)
          if (s[j] == '+')
            s[j] = '-';
          else
            s[j] = '+';
        ans++;
      }
    }
    for (int i = (0); i <= (((int)s.size()) - 1); ++i)
      if (s[i] == '-') {
        ans = -1;
        break;
      }
    cout << "Case #" << x << ": ";
    if (ans == -1)
      cout << "IMPOSSIBLE\n";
    else
      cout << ans << endl;
  }
  return 0;
}
