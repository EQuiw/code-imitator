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
const int MAXN = 100;
const int SQRTN = 550;
const int LOGN = 60;
const int INT_INFINITY = 1001001001;
const int LIMIT = 1e6;

const slong LONG_INFINITY = 1001001001001001001ll;
const slong LONG_LIMIT = 200100100100101ll;

const double DOUBLE_INFINITY = 1e16;

int n, q;
int arr[MAXN + 5][MAXN + 5];
int e[MAXN + 5];
int s[MAXN + 5];

double dp[MAXN + 5];

int main() {

  cout.tie(0);
  cin.tie(0);

  int t, T, i, j;

  cin >> T;

  for (t = 1; t <= T; t++) {
    cin >> n >> q;

    for (i = 1; i <= n; i++) {
      cin >> e[i] >> s[i];
    }

    for (i = 1; i <= n; i++) {
      for (j = 1; j <= n; j++) {
        cin >> arr[i][j];
      }
    }

    cout << "Case #" << t << ":";

    while (q--) {
      int u, v;
      cin >> u >> v;

      for (i = 1; i <= n; i++) {
        dp[i] = DOUBLE_INFINITY;
      }

      dp[v] = 0;

      for (i = n; i >= 1; i--) {
        slong currdis = 0;
        for (j = i + 1; j <= n; j++) {
          // try from i->j
          currdis += arr[j - 1][j];
          assert(arr[j - 1][j] != -1);

          {
            if (e[i] >= currdis) {
              double curr = currdis * 1.0 / s[i];
              dp[i] = min(dp[i], curr + dp[j]);
            }
          }
        }
      }

      double ans = dp[u];
      cout << " " << fixed << setprecision(10) << ans;
    }

    cout << endl;
  }

  return 0;
}
