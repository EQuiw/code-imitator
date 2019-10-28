#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;
typedef unsigned long long ull;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> pii;

const int OO = (int)2e9;
const double eps = 1e-9;

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  //#ifndef ONLINE_JUDGE
  freopen("A-small-attempt0.in", "rt", stdin);
  freopen("out.txt", "wt", stdout);
  //#endif
  int t, tt = 1;
  cin >> t;
  while (t--) {
    string s;
    int n, k, res = 0;
    bool ok = 1;
    cin >> s >> k;
    n = ((int)(s).size());
    for (int i = 0; i <= n - k; i++) {
      if (s[i] == '-') {
        for (int j = 0; j < k; j++) {
          s[i + j] = (s[i + j] == '+') ? '-' : '+';
        }
        res++;
      }
    }
    for (int i = 0; i < n; i++) {
      if (s[i] == '-') {
        ok = 0;
        break;
      }
    }
    if (ok)
      cout << "Case #" << tt++ << ": " << res << "\n";
    else
      cout << "Case #" << tt++ << ": "
           << "IMPOSSIBLE"
           << "\n";
  }
  return 0;
}
