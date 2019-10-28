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

int n, k;
bool bad[N];

pair<int, int> calc(int p) {
  pair<int, int> res = {0, 0};
  for (int i = p; i <= n; i++) {
    if (bad[i]) {
      break;
    }
    res.second++;
  }
  for (int i = p; i >= 1; i--) {
    if (bad[i]) {
      break;
    }
    res.first++;
  }
  return res;
}

pair<int, int> get(pair<int, int> l, pair<int, int> r) {
  if (min(l.first, l.second) > min(r.first, r.second))
    return l;
  if (min(l.first, l.second) < min(r.first, r.second))
    return r;
  if (max(l.first, l.second) > max(r.first, r.second))
    return l;
  return r;
}

void solve(int id) {
  scanf("%d%d", &n, &k);
  memset(bad, 0, sizeof(bad));
  for (int i = 1; i <= k; i++) {
    pair<int, int> mx = {-1, -1};
    int idx = -1;
    for (int j = 1; j <= n; j++) {
      pair<int, int> cur = calc(j);
      pair<int, int> res = get(mx, cur);
      if (mx != res)
        idx = j, mx = res;
    }
    if (i == k) {
      cout << "Case #" << id << ": " << max(mx.first, mx.second) - 1 << ' '
           << min(mx.first, mx.second) - 1 << '\n';
      return;
    }
    bad[idx] = 1;
  }
}

int T;
int main() {

  freopen("C-small-1-attempt4"
          ".in",
          "r", stdin);
  freopen("C-small-1-attempt4"
          ".out",
          "w", stdout);

  scanf("%d", &T);
  for (int i = 1; i <= T; i++)
    solve(i);
  exit(0);
}
