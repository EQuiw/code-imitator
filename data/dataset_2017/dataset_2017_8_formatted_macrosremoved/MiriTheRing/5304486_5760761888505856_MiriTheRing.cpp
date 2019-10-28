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
  for (ll tc = (0); tc < (TC); tc++) {
    ll r, c;
    cin >> r >> c;
    vector<vector<char>> g = vector<vector<char>>(r, vector<char>(c));
    for (ll i = (0); i < (r); i++) {
      for (ll j = (0); j < (c); j++) {
        cin >> g[i][j];
      }
    }
    stack<ll> todo;
    vector<bool> done(r, false);
    for (ll i = (0); i < (r); i++) {
      for (ll j = (0); j < (c); j++) {
        if (g[i][j] != '?') {
          todo.push(i);
          break;
        }
      }
    }
    while (!todo.empty()) {
      ll i = todo.top();
      todo.pop();
      done[i] = true;
      char cc = '?';
      for (ll j = (0); j < (c); j++) {
        if (g[i][j] != '?') {
          cc = g[i][j];
          break;
        }
      }
      if (cc == '?') {
        if (i > 0 && done[i - 1]) {
          for (ll j = (0); j < (c); j++) {
            g[i][j] = g[i - 1][j];
          }
        } else {
          for (ll j = (0); j < (c); j++) {
            g[i][j] = g[i + 1][j];
          }
        }
      } else {
        for (ll j = (0); j < (c); j++) {
          if (g[i][j] == '?') {
            g[i][j] = cc;
          } else {
            cc = g[i][j];
          }
        }
      }
      if (i > 0 && !done[i - 1])
        todo.push(i - 1);
      if (i < r - 1 && !done[i + 1])
        todo.push(i + 1);
    }
    cout << "Case #" << tc + 1 << ":" << endl;
    for (ll i = (0); i < (r); i++) {
      for (ll j = (0); j < (c); j++) {
        cout << g[i][j];
      }
      cout << endl;
    }
  }
}
