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
  freopen("B-small-attempt0.in", "rt", stdin);
  freopen("out.txt", "wt", stdout);
  //#endif
  int t, tt = 1;
  cin >> t;
  while (t--) {
    string s;
    int n;
    cin >> s;
    n = ((int)(s).size());
    string res = string(n - 1, '9');
    for (int i = 1; i < n; i++) {
      if (s[i] < s[i - 1]) {
        s[i - 1]--;
        int idx = i;
        for (int j = i - 2; j >= 0; j--) {
          if (s[j] > s[j + 1]) {
            idx = j + 1;
            s[j]--;
          } else {
            break;
          }
        }
        for (int j = idx; j < n; j++) {
          s[j] = '9';
        }
        break;
      }
    }
    if (s[0] != '0') {
      res = s;
    }
    cout << "Case #" << tt++ << ": " << res << "\n";
  }
  return 0;
}
