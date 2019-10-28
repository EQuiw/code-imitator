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

int calcLevel(ll x) {
  int res = 0;
  while (x) {
    x >>= 1;
    res++;
  }
  return res - 1;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  //#ifndef ONLINE_JUDGE
  freopen("C-small-1-attempt2.in", "rt", stdin);
  freopen("out.txt", "wt", stdout);
  //#endif
  int t, tt = 1;
  cin >> t;
  while (t--) {
    ll n, k, mn, mx;
    cin >> n >> k;
    int lvl = calcLevel(k);
    for (int i = 0; i < lvl; i++) {
      mn = (n - 1) >> 1, mx = (n - 1) - mn;
      if (k & (1LL << i)) {
        n = mn;
      } else {
        n = mx;
      }
    }
    mn = (n - 1) >> 1, mx = (n - 1) - mn;
    cout << "Case #" << tt++ << ": " << mx << " " << mn << "\n";
  }
  return 0;
}
