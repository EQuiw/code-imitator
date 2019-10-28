/*
 * Author: Vladislav Belov
 */
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

void solution();

int main() {
  ios::sync_with_stdio(false);

  solution();

  return EXIT_SUCCESS;
}

typedef long long ll;

pair<ll, ll> solve_naive(ll n, ll k) {
  vector<char> u(n + 2);
  u[0] = u[n + 1] = 1;
  ll last_ls = -1, last_rs = -1;
  for (ll i = 0; i < k; ++i) {
    ll index = -1, dist = -1, dist_max = -1;
    for (ll i = 1; i <= n; ++i) {
      if (u[i])
        continue;
      ll ls = i, rs = i;
      while (!u[ls])
        --ls;
      while (!u[rs])
        ++rs;
      ll d_min = min(i - ls, rs - i);
      ll d_max = max(i - ls, rs - i);
      if (index == -1 || dist < d_min || (dist == d_min && dist_max < d_max)) {
        dist = d_min;
        dist_max = d_max;
        index = i;
        last_ls = i - ls - 1;
        last_rs = rs - i - 1;
      }
    }
    u[index] = 1;
  }
  return make_pair(max(last_ls, last_rs), min(last_ls, last_rs));
}

ll power(ll n) {
  for (ll i = 1;; i *= 2)
    if (i > n)
      return i;
  return 0;
}

pair<ll, ll> solve(ll n, ll k) {
  ll first = 0, second = 0;
  ll pwr = power(k);
  ll m = k - pwr / 2;
  first = (n - m) / pwr;
  second = (n - k) / pwr;
  return make_pair(first, second);
}

void solution() {
  /*
  const int N = 500;
  cout << "   k:  | ";
  for (int k = 1; k <= N; ++k)
      cout << setw(4) << k << "    |";
  cout << endl;
  cout << "-------+-";
  for (int k = 1; k <= N; ++k)
      cout << "----" << "----+";
  cout << endl;
  for (int n = 1; n <= N; ++n)
  {
      cout << "n: " << setw(3) << n << " | ";
      for (int k = 1; k <= n; ++k)
      {
          pair<int,int> ans = solve_naive(n, k);
          pair<int,int> ans2 = solve(n, k);
          if (ans2 != ans)
          {
              cerr << "FAIL" << n << " " << k << endl;
          }
          cout << setw(4) << ans.first << setw(4) << ans.second << "|";
      }
      cout << endl;
  }
  return;
  */
  ll T;
  cin >> T;
  for (ll t = 0; t < T; ++t) {
    cerr << t + 1 << endl;
    ll n, k;
    cin >> n >> k;
    pair<ll, ll> ans = solve(n, k);
    cout << "Case #" << t + 1 << ": " << ans.first << " " << ans.second << '\n';
  }
}
