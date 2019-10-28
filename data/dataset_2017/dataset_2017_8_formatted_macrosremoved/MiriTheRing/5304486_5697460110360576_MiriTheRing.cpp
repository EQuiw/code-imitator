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
    cout << "Case #" << tc + 1 << ": ";
    ll n, p;
    cin >> n >> p;
    vector<ll> r(n);
    vector<vector<ll>> q(n, vl(p));
    for (ll i = (0); i < (n); i++)
      cin >> r[i];
    for (ll i = (0); i < (n); i++) {
      for (ll j = (0); j < (p); j++) {
        cin >> q[i][j];
      }
      sort(begin(q[i]), end(q[i]));
    }
    vector<vector<pll>> add(n, vector<pll>());
    vl idx(n, 0);
    ll res = 0;
    bool done = false;
    while (!done) {
      ll larger_than = -oo;
      for (ll i = (0); i < (n); i++) {
        larger_than = max(larger_than, (ll)ceil(q[i][idx[i]] / (1.1 * r[i])));
      }
      bool poss = true;
      ll largest_min_inc = -oo;
      ll largest_min_inc_idx = 0;
      for (ll i = (0); i < (n); i++) {
        ll smaller_than = floor(q[i][idx[i]] / (0.9 * r[i]));
        if (smaller_than < larger_than) {
          ll min_inc = ceil(larger_than * 0.9 * r[i] - q[i][idx[i]]);
          if (min_inc > largest_min_inc) {
            largest_min_inc = min_inc;
            largest_min_inc_idx = i;
          }
          auto ptr =
              lower_bound(begin(add[i]), end(add[i]), make_pair(min_inc, 0ll));
          if (ptr == add[i].end()) {
            poss = false;
            break;
          }
        }
      }
      if (poss) {
        res++;
        for (ll i = (0); i < (n); i++) {
          ll smaller_than = floor(q[i][idx[i]] / (0.9 * r[i]));
          if (smaller_than < larger_than) {
            ll min_inc = ceil(larger_than * 0.9 * r[i] - q[i][idx[i]]);
            auto ptr = lower_bound(begin(add[i]), end(add[i]),
                                   make_pair(min_inc, 0ll));
            vector<pll> new_add = vector<pll>();
            for (ll j = (0); j < (ll((add[i]).size())); j++) {
              if (!(add[i][j].second & ptr->second)) {
                new_add.push_back(add[i][j]);
              }
            }
            sort(begin(new_add), end(new_add));
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
        vector<pll> new_add = vector<pll>(begin(add[i]), end(add[i]));
        for (ll j = (0); j < (ll((add[i]).size())); j++) {
          new_add.push_back(
              make_pair(add[i][j].first + add_val, (add[i][j].second | pos)));
        }
        sort(begin(new_add), end(new_add));
        add[i] = new_add;
      }
    }
    cout << res << endl;
  }
}
