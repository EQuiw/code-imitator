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

string encode(ll p, ll n) {
  string s = "";
  FOR(i, 0, n) {
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
  FOR(i, 0, n - k + 1) {
    ll pnew = p;
    FOR(j, 0, k) {
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
  FOR(tc, 0, TC) {
    string s;
    cin >> s;
    ll k, n;
    cin >> k;
    n = sz(s);
    ll p = 0;
    FOR(i, 0, sz(s)) {
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
    FOR(i, 0, n - k + 1) {
      if (p & (1 << (i))) {
        FOR(j, 0, k) {
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
