#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1234567890123LL;

void solve() {
  ll n, k;
  cin >> n >> k;

  ll maximum = 0, minimum = INF;

  set<ll> s;
  map<ll, ll> m;
  ll done = 0;

  s.insert(n);
  m[n] = 1;
  while (1) {
    ll v = *s.rbegin();
    // printf(" v= %lld , m[v] = %lld\n", v,m[v]);

    done += m[v];

    ll a = (v - 1) / 2;
    ll b = v - 1 - a;

    if (done >= k) {
      maximum = max(a, b);
      minimum = min(a, b);
      break;
    }

    m[a] += m[v];
    m[b] += m[v];
    s.erase(v);
    s.insert(a);
    s.insert(b);
  }

  assert(maximum >= minimum);
  printf("%lld %lld\n", maximum, minimum);
}

int main() {
  int T;
  cin >> T;
  for (int(t) = 0; (t) < (int)(T); ++(t)) {
    printf("Case #%d: ", t + 1);
    solve();
  }
  return 0;
}
