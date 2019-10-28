#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;

const int N = 1e6 + 7, inf = 1e9 + 7, mod = 1e9 + 7;
const ll linf = (ll)1e18 + 7;
const int dx[] = {-1, 0, 1, 0, 1, -1, -1, 1},
          dy[] = {0, 1, 0, -1, 1, -1, 1, -1};

int n;
double d;
double k[N], second[N];
void solve(int id) {
  cin >> d >> n;
  for (int i = 1; i <= n; i++)
    cin >> k[i] >> second[i];
  double res = -linf;
  for (int i = 1; i <= n; i++)
    res = max(res, (d - k[i]) / second[i]);
  cout << "Case #" << id << ": " << setprecision(10) << fixed << d / res
       << '\n';
}
int main() {

  freopen("A-small-attempt0"
          ".in",
          "r", stdin);
  freopen("A-small-attempt0"
          ".out",
          "w", stdout);

  ios_base ::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T = 1;
  cin >> T;
  for (int i = 1; i <= T; i++)
    solve(i);
  exit(0);
}
