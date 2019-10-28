// Written by Li Bo
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, k;
ll a, b, c;

inline void div(ll a, ll &b, ll &c) {
  a--;
  b = a >> 1;
  c = a - b;
  if (b < c)
    swap(b, c);
}

map<ll, ll, greater<ll>> res;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; cas++) {
    a = b = c = 0;
    cin >> n >> k;

    res.clear();

    res[n] = 1;

    ll ans;
    while (true) {
      auto x = res.begin();
      ll num = x->first, cc = x->second;
      if (cc >= k) {
        ans = num;
        break;
      }
      k -= cc;
      ll a, b;
      div(num, a, b);
      res.erase(x);
      res[a] += cc;
      res[b] += cc;
    }

    printf("Case #%d: ", cas);
    ll a, b;
    div(ans, a, b);
    cout << a << " " << b;

    puts("");
  }
  return 0;
}
