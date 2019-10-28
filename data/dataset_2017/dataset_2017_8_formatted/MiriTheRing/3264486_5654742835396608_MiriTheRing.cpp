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

void compute(ll n, ll l, ll h) {
  if (h == 0) {
    cout << (l) / 2 << " " << (l - 1) / 2 << endl;
    return;
  }
  if (n > (1 << h) / 2) {
    compute(n - (1 << h) / 2, l / 2, h - 1);
  } else {
    compute(n, (l - 1) / 2, h - 1);
  }
}

int main() {
  ios::sync_with_stdio(false);
  ll TC;
  cin >> TC;
  FOR(tc, 0, TC) {
    ll l, n;
    cin >> l >> n;
    map<ll, ll> h;
    priority_queue<ll> q;
    h[l] = 1;
    q.push(l);
    cout << "Case #" << tc + 1 << ": ";
    while (n > 0) {
      ll nl = q.top();
      while (!q.empty() && q.top() == nl)
        q.pop();
      n -= h[nl];
      h[nl / 2] += h[nl];
      h[(nl - 1) / 2] += h[nl];
      h[nl] = 0;
      if (n <= 0) {
        cout << nl / 2 << " " << (nl - 1) / 2 << endl;
      }
      q.push(nl / 2);
      q.push((nl - 1) / 2);
    }
  }
}
