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

const int N = 4e5 + 7, inf = 1e9 + 7, mod = 1e9 + 7;
const ll linf = (ll)1e18 + 7;
const int dx[] = {-1, 0, 1, 0, 1, -1, -1, 1},
          dy[] = {0, 1, 0, -1, 1, -1, 1, -1};

int n, k, t;
int d[1 << 14];
string second;

int get_mask(string x) {
  int res = 0;
  reverse(x.begin(), x.end());
  for (int i = 0; i <= (int)x.size() - 1; i++)
    if (x[i] == '+')
      res |= 1 << i;
  return res;
}
int inverse(int l, int x) {
  for (int i = l; i <= l + k - 1; i++)
    x ^= 1 << i;
  return x;
}

void solve(int id) {
  cin >> second >> k;
  n = (int)second.size();

  memset(d, -1, sizeof(d));
  queue<int> q;
  int st = get_mask(second);
  d[st] = 0;
  q.push(st);

  while ((int)q.size()) {
    int v = q.front();
    q.pop();
    for (int i = 0; i <= n - 1 - k + 1; i++) {
      int x = inverse(i, v);
      if (d[x] == -1)
        d[x] = d[v] + 1, q.push(x);
    }
  }

  int res = d[(1 << n) - 1];
  cout << "Case #" << id << ": ";
  if (res == -1)
    cout << "IMPOSSIBLE" << '\n';
  else
    cout << res << '\n';
}
int main() {

  //  freopen ("A-small-attempt0.in", "r", stdin);
  cin >> t;
  for (int i = 1; i <= t; i++)
    solve(i);
  exit(0);
}
