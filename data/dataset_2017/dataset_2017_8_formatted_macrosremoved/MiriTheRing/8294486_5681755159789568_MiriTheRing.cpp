#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using pll = pair<ll, ll>;
using vb = vector<bool>;
const ll oo = 0x3f3f3f3f3f3f3f3fLL;
const double eps = 1e-9;
int main() {
  ios::sync_with_stdio(false);
  ll TC;
  cin >> TC;
  for (ll tc = (1); tc < (TC + 1); tc++) {
    cout << "Case #" << tc << ": ";
    ll n, q;
    cin >> n >> q;
    vector<double> e(n), s(n);
    for (ll i = (0); i < (n); i++) {
      cin >> e[i] >> s[i];
    }
    vector<vl> d(n, vl(n));
    vector<vector<double>> t(n, vector<double>(n, oo));
    for (ll i = (0); i < (n); i++) {
      for (ll j = (0); j < (n); j++) {
        cin >> d[i][j];
        if (d[i][j] == -1) {
          d[i][j] = oo;
        }
      }
    }

    for (ll k = (0); k < (n); k++) {
      for (ll i = (0); i < (n); i++) {
        for (ll j = (0); j < (n); j++) {
          if (d[i][j] > d[i][k] + d[k][j]) {
            d[i][j] = d[i][k] + d[k][j];
          }
        }
      }
    }

    for (ll i = (0); i < (n); i++) {
      for (ll j = (0); j < (n); j++) {
        if (d[i][j] <= e[i]) {
          t[i][j] = d[i][j] / s[i];
        }
      }
    }

    for (ll k = (0); k < (n); k++) {
      for (ll i = (0); i < (n); i++) {
        for (ll j = (0); j < (n); j++) {
          if (t[i][j] > t[i][k] + t[k][j]) {
            t[i][j] = t[i][k] + t[k][j];
          }
        }
      }
    }

    for (ll i = (0); i < (q); i++) {
      ll u, v;
      cin >> u >> v;
      cout << setprecision(8) << fixed << t[u - 1][v - 1] << " ";
    }
    cout << endl;
  }
}
