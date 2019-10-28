#include <bits/stdc++.h>

using namespace std;
using ll = long long;

pair<ll, ll> solve(ll n, ll k) {
  if (k == 1)
    return make_pair(n / 2, (n - 1) / 2);
  if ((k & 1) == 0) {
    return solve(n / 2, k / 2);
  } else {
    return solve((n - 1) / 2, k / 2);
  }
}

int main() {
  ios::sync_with_stdio(false);

  int T;
  cin >> T;

  for (int t = 1; t <= T; t++) {
    ll n, k;
    cin >> n >> k;
    auto p = solve(n, k);
    cout << "Case #" << t << ": ";
    cout << p.first << " " << p.second << "\n";
  }

  return 0;
}
