#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
typedef long long int slong;
typedef pair<int, int> pii;
typedef pair<slong, slong> pll;
typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    pbds;
typedef set<int>::iterator sit;
typedef map<int, int>::iterator mit;
typedef vector<int>::iterator vit;

const int MOD = 1000000007;
const int MAXN = 1000;
const int SQRTN = 550;
const int LOGN = 60;
const int INT_INFINITY = 1001001001;
const int LIMIT = 1e6;

const slong LONG_INFINITY = 1001001001001001001ll;
const slong LONG_LIMIT = 200100100100101ll;

int d, n;
int k[MAXN + 5], s[MAXN + 5];

int main() {

  cout.tie(0);
  cin.tie(0);

  int t, T, i, j;

  cin >> T;

  for (t = 1; t <= T; t++) {
    cin >> d >> n;

    double maxtime = 0;

    for (i = 1; i <= n; i++) {
      cin >> k[i] >> s[i];
      int leftdis = d - k[i];
      double time = leftdis * 1.0 / s[i];
      maxtime = max(maxtime, time);
    }

    double s = d / maxtime;

    cout << "Case #" << t << ": " << fixed << setprecision(10) << s << endl;
  }

  return 0;
}
