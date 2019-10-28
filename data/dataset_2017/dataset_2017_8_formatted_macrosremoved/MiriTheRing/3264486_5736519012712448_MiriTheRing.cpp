#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using pll = pair<ll, ll>;
using vb = vector<bool>;
const ll oo = 0x3f3f3f3f3f3f3f3fLL;
const double eps = 1e-9;
string encode(ll p, ll n) {
  string s = "";
  for (ll i = (0); i < (n); i++) {
    if (p & (1 << i)) {
      s += "+";
    } else {
      s += "-";
    }
  }
  return s;
}

void compute(ll p, vl &dp, ll k, ll n) {
  if (dp[p] != oo)
    return;
  dp[p] = oo - 1;
  for (ll i = (0); i < (n - k + 1); i++) {
    ll pnew = p;
    for (ll j = (0); j < (k); j++) {
      if (p & (1 << (i + j))) {
        pnew &= ~(1 << (i + j));
      } else {
        pnew |= 1 << (i + j);
      }
    }
    compute(pnew, dp, k, n);
    dp[p] = min(dp[pnew] + 1, dp[p]);
  }
}

int main() {
  ios::sync_with_stdio(false);
  ll TC;
  cin >> TC;
  for (ll tc = (0); tc < (TC); tc++) {
    string s;
    cin >> s;
    ll k, n;
    cin >> k;
    n = ll((s).size());
    ll p = 0;
    for (ll i = (0); i < (ll((s).size())); i++) {
      if (s[i] == '-')
        p |= (1 << i);
    }
    /*
    vl dp((1<<11), oo);
    dp[p] = 0;
    compute(0, dp, k, n);
    */
    cout << "Case #" << tc + 1 << ": ";
    /*
    if(dp[0] < oo-1){
      cout << dp[0] << endl;
    } else {
      cout << "IMPOSSIBLE" << endl;
    }
    */

    ll res = 0;
    for (ll i = (0); i < (n - k + 1); i++) {
      if (p & (1 << (i))) {
        for (ll j = (0); j < (k); j++) {
          if (p & (1 << (i + j))) {
            p &= ~(1 << (i + j));
          } else {
            p |= 1 << (i + j);
          }
        }
        res++;
      }
    }
    if (p == 0)
      cout << res << endl;
    else
      cout << "IMPOSSIBLE" << endl;
  }
}
