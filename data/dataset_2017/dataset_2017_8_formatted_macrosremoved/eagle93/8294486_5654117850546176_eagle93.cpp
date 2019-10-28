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

const int N = 1003;

int n;
int c[6];
string col = "ROYGBV";

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  //#ifndef ONLINE_JUDGE
  freopen("B-small-attempt0.in", "rt", stdin);
  freopen("out.txt", "wt", stdout);
  //#endif
  int t, tt = 1;
  cin >> t;
  while (t--) {
    cin >> n;
    bool ok = 1;
    for (int i = 0; i < 6; i++) {
      cin >> c[i];
      if (c[i] * 2 > n) {
        ok = 0;
      }
    }
    int prv = -1;
    string res;
    for (int i = 0; i < n; i++) {
      int mx = 0, idx = -1;
      for (int j = 0; j < 6; j += 2) {
        if (c[j] >= mx && j != prv) {
          mx = c[j], idx = j;
        }
      }
      res += col[idx];
      prv = idx;
      c[idx]--;
    }
    if (!ok)
      cout << "Case #" << tt++ << ": "
           << "IMPOSSIBLE"
           << "\n";
    else
      cout << "Case #" << tt++ << ": " << res << "\n";
  }
  return 0;
}
