#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using pll = pair<ll, ll>;
using vb = vector<bool>;
const ll oo = 0x3f3f3f3f3f3f3f3fLL;
const double eps = 1e-9;
#define sz(c) ll((c).size())
#define all(c) begin(c), end(c)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define xx first
#define yy second
#define has(c, i) ((c).find(i) != end(c))
#define FOR(i, a, b) for (ll i = (a); i < (b); i++)
#define FORD(i, a, b) for (ll i = (b)-1; i >= (a); i--)

int main() {
  ios::sync_with_stdio(false);
  ll TC;
  cin >> TC;
  FOR(tc, 0, TC) {
    ll r, c;
    cin >> r >> c;
    vector<vector<char>> g = vector<vector<char>>(r, vector<char>(c));
    FOR(i, 0, r) {
      FOR(j, 0, c) { cin >> g[i][j]; }
    }
    stack<ll> todo;
    vector<bool> done(r, false);
    FOR(i, 0, r) {
      FOR(j, 0, c) {
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
      FOR(j, 0, c) {
        if (g[i][j] != '?') {
          cc = g[i][j];
          break;
        }
      }
      if (cc == '?') {
        if (i > 0 && done[i - 1]) {
          FOR(j, 0, c) { g[i][j] = g[i - 1][j]; }
        } else {
          FOR(j, 0, c) { g[i][j] = g[i + 1][j]; }
        }
      } else {
        FOR(j, 0, c) {
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
    FOR(i, 0, r) {
      FOR(j, 0, c) { cout << g[i][j]; }
      cout << endl;
    }
  }
}
