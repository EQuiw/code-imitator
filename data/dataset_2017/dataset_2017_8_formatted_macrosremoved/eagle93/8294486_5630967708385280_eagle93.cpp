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

int n, d;
int k[N], s[N];

double dist(int v1, int d1, int v2, int d2) {
  if (v1 <= v2) {
    return (double)d1 / v1;
  }
  double st = 0, size = OO;
  for (; size > eps; size *= 0.5) {
    double t = st + size;
    if (v1 * t >= v2 * t)
      st += size;
  }
  double rem = d - st * v1;
  return st + rem / v2;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  //#ifndef ONLINE_JUDGE
  freopen("A-small-attempt1.in", "rt", stdin);
  freopen("out.txt", "wt", stdout);
  //#endif
  int t, tt = 1;
  cin >> t;
  while (t--) {
    cin >> d >> n;
    for (int i = 0; i < n; i++)
      cin >> k[i] >> s[i];
    s[n] = OO;
    double res = 0;
    for (int i = n - 1; i >= 0; i--) {
      res = max(res, double(d - k[i]) / s[i]);
    }
    cout << fixed << setprecision(6);
    cout << "Case #" << tt++ << ": " << d / res << "\n";
  }
  return 0;
}
