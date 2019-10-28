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

const int N = 4686825 + 7, inf = 1e9 + 7, mod = 1e9 + 7;
const ll linf = (ll)1e18 + 7;
const int dx[] = {-1, 0, 1, 0, 1, -1, -1, 1},
          dy[] = {0, 1, 0, -1, 1, -1, 1, -1};

int n, t;
ll a[N];

void gen() {
  queue<ll> q;
  for (int i = 1; i <= 9; i++)
    q.push(i);
  while ((int)q.size()) {
    ll v = q.front();
    q.pop();

    if (v < (ll)1e18) {
      a[++n] = v;
      for (int i = v % 10; i <= 9; i++)
        q.push(v * 10 + i);
    }
  }
}

void solve(int id) {
  ll x;
  cin >> x;
  int pos = upper_bound(a + 1, a + 1 + n, x) - a - 1;
  cout << "Case #" << id << ": " << a[pos] << '\n';
}
int main() {

  ios_base ::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> t;
  gen();
  for (int i = 1; i <= t; i++)
    solve(i);

  exit(0);
}
