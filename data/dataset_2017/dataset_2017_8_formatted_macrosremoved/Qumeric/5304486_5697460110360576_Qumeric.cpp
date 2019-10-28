#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const ll MAX = 1e6 + 777;

int isfine1(ll r, ll p) {
  if (false)
    cerr << "ISFINE1: " << r << ' ' << p << endl;
  ll x = 0;
  while (++x < MAX) {
    if (p * 10 >= x * r * 9 && p * 10 <= x * r * 11) {
      if (false)
        cerr << "returns ok" << endl;
      return 1; // it's fine
    }
  }
  if (false)
    cerr << "returns no" << endl;
  return 0;
}

bool isfine2(const vector<ll> &r, const vector<ll> &p) {
  if (false)
    cerr << "ISFINE2 GOT: " << endl;
  if (false)
    cerr << "R: " << r[0] << ' ' << r[1] << endl;
  if (false)
    cerr << "P: " << p[0] << ' ' << p[1] << endl;
  ll x = 0;
  ll l = 1, rt = 1e6 + 1;
  while (l < rt) {
    ll x = (l + rt) / 2;
    if (p[0] * 10 >= x * r[0] * 9 && p[0] * 10 <= x * r[0] * 11 &&
        p[1] * 10 >= x * r[1] * 9 && p[1] * 10 <= x * r[1] * 11) {
      return true; // it's fine
    }
    if (p[0] * 10 > x * r[0] * 11 || p[1] * 10 > x * r[1] * 11) {
      l = x + 1;
    }
    if (p[0] * 10 < x * r[0] * 9 || p[1] * 10 < x * r[1] * 9) {
      rt = x;
    }
  }

  // just in case
  if (p[0] * 10 >= l * r[0] * 9 && p[0] * 10 <= l * r[0] * 11 &&
      p[1] * 10 >= l * r[1] * 9 && p[1] * 10 <= l * r[1] * 11) {
    return true; // it's fine
  }
  if (p[0] * 10 >= rt * r[0] * 9 && p[0] * 10 <= rt * r[0] * 11 &&
      p[1] * 10 >= rt * r[1] * 9 && p[1] * 10 <= rt * r[1] * 11) {
    return true; // it's fine
  }
  return false;
}

ll t, n, p;
inline void solve() {
  cin >> n >> p;
  vector<ll> r(n);
  vector<vector<ll>> q(n, vector<ll>(p));
  for (int i = 0; i < n; i++) {
    cin >> r[i];
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < p; j++) {
      cin >> q[i][j];
    }
  }

  for (int i = 0; i < n; i++)
    sort(q[i].begin(), q[i].end());

  ll anw = 0;
  if (n == 1) {
    for (int i = 0; i < p; i++) {
      if (isfine1(r[0], q[0][i]))
        anw++;
    }
    cout << anw << '\n';
    return;
  }
  do {
    ll res = 0;
    for (int i = 0; i < p; i++) {
      vector<ll> cv(2);
      cv[0] = q[0][i];
      cv[1] = q[1][i];
      res += (isfine2(r, cv));
    }
    anw = max(anw, res);
  } while (next_permutation(q[0].begin(), q[0].end()));
  cout << anw << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cout << "Case #" << i << ":\n";
    solve();
  }
}
