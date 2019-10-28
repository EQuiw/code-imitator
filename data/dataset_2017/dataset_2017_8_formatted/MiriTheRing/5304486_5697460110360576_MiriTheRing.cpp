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
    cout << "Case #" << tc + 1 << ": ";
    ll n, p;
    cin >> n >> p;
    vector<ll> r(n);
    vector<vector<ll>> q(n, vl(p));
    FOR(i, 0, n) cin >> r[i];
    FOR(i, 0, n) {
      FOR(j, 0, p) { cin >> q[i][j]; }
      sort(all(q[i]));
    }
    vector<vector<pll>> add(n, vector<pll>());
    vl idx(n, 0);
    ll res = 0;
    bool done = false;
    while (!done) {
      ll larger_than = -oo;
      FOR(i, 0, n) {
        larger_than = max(larger_than, (ll)ceil(q[i][idx[i]] / (1.1 * r[i])));
      }
      bool poss = true;
      ll largest_min_inc = -oo;
      ll largest_min_inc_idx = 0;
      FOR(i, 0, n) {
        ll smaller_than = floor(q[i][idx[i]] / (0.9 * r[i]));
        if (smaller_than < larger_than) {
          ll min_inc = ceil(larger_than * 0.9 * r[i] - q[i][idx[i]]);
          if (min_inc > largest_min_inc) {
            largest_min_inc = min_inc;
            largest_min_inc_idx = i;
          }
          auto ptr = lower_bound(all(add[i]), mp(min_inc, 0ll));
          if (ptr == add[i].end()) {
            poss = false;
            break;
          }
        }
      }
      if (poss) {
        res++;
        FOR(i, 0, n) {
          ll smaller_than = floor(q[i][idx[i]] / (0.9 * r[i]));
          if (smaller_than < larger_than) {
            ll min_inc = ceil(larger_than * 0.9 * r[i] - q[i][idx[i]]);
            auto ptr = lower_bound(all(add[i]), mp(min_inc, 0ll));
            vector<pll> new_add = vector<pll>();
            FOR(j, 0, sz(add[i])) {
              if (!(add[i][j].yy & ptr->yy)) {
                new_add.pb(add[i][j]);
              }
            }
            sort(all(new_add));
            add[i] = new_add;
          }
          idx[i]++;
          if (idx[i] == p)
            done = true;
        }
      } else {
        ll i = largest_min_inc_idx;
        ll add_val = q[i][idx[i]];
        ll pos = idx[i];
        idx[i]++;
        if (idx[i] == p)
          done = true;
        vector<pll> new_add = vector<pll>(all(add[i]));
        FOR(j, 0, sz(add[i])) {
          new_add.pb(mp(add[i][j].xx + add_val, (add[i][j].yy | pos)));
        }
        sort(all(new_add));
        add[i] = new_add;
      }
    }
    cout << res << endl;
  }
}
