#include <bits/stdc++.h>
#define rep(i, start, lim) for (lld i = start; i < lim; i++)
#define repd(i, start, lim) for (lld i = start; i >= lim; i--)
#define scan(x) scanf("%lld", &x)
#define print(x) printf("%lld ", x)
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define br printf("\n")
#define sz(a) lld((a).size())
#define YES printf("YES\n")
#define NO printf("NO\n")
#define all(c) (c).begin(), (c).end()
using namespace std;
#define INF 1011111111
#define LLINF 1000111000111000111LL
#define EPS (double)1e-10
#define MOD 1000000007
#define PI 3.14159265358979323
using namespace std;
typedef long double ldb;
typedef long long lld;
lld powm(lld base, lld exp, lld mod = MOD) {
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
#define N 100005
lld a[N], prv[N], nxt[N];
int main() {
  freopen("done5.in", "r", stdin);
  freopen("done5.out", "w", stdout);
  lld t, n, k, ind, maxm;
  cin >> t;
  rep(tt, 1, t + 1) {
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
