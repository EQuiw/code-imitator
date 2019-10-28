#include <bits/stdc++.h>
using namespace std;

using namespace std;
typedef long double ldb;
typedef long long lld;
lld powm(lld base, lld exp, lld mod = 1000000007) {
  lld ans = 1;
  while (exp) {
    if (exp & 1)
      ans = (ans * base) % mod;
    exp >>= 1, base = (base * base) % mod;
  }
  return ans;
}
typedef vector<lld> vlld;
typedef pair<lld, lld> plld;
typedef map<lld, lld> mlld;
typedef set<lld> slld;

lld a[100005], prv[100005], nxt[100005];
int main() {
  freopen("done5.in", "r", stdin);
  freopen("done5.out", "w", stdout);
  lld t, n, k, ind, maxm;
  cin >> t;
  for (lld tt = 1; tt < t + 1; tt++) {
    cin >> n >> k;
    priority_queue<lld> pq;
    pq.push(n);
    while (k-- > 1) {
      lld curr = pq.top();
      pq.pop(), pq.push(curr / 2), pq.push(curr - 1 - (curr / 2));
    }
    lld curr = pq.top(), a1 = (curr / 2), a2 = (curr - 1 - (curr / 2));
    cout << "Case #" << tt << ": " << max(a1, a2) << " " << min(a1, a2) << endl;
  }
  return 0;
}
