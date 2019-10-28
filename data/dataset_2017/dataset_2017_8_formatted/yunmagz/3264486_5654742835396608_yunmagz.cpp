#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define zero(x) (((x) > 0 ? (x) : -(x)) < eps)
typedef vector<int> VI;
typedef long long LL;
typedef pair<int, int> PII;
const double eps = 1e-8;
const double pi = acos(-1.0);
const int inf = 0x3f3f3f3f;
const int INF = 2e9 + 7;
const int mod = 1e9 + 7;
LL powmod(LL a, LL b) {
  LL res = 1;
  a %= mod;
  assert(b >= 0);
  for (; b; b >>= 1) {
    if (b & 1)
      res = res * a % mod;
    a = a * a % mod;
  }
  return res;
}
int a[1010];
priority_queue<int> q;
int main() {
  freopen("C-small-1-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);
  int t, k, cas = 1;
  int n, m;
  cin >> t;
  while (t--) {
    cin >> n >> k;
    printf("Case #%d: ", cas++);
    while (!q.empty())
      q.pop();
    q.push(n);
    int l, r;
    while (k--) {
      int m = q.top();
      q.pop();
      if (m & 1)
        l = r = m >> 1;
      else
        r = m >> 1, l = (m >> 1) - 1;
      q.push(l);
      q.push(r);
    }
    cout << r << " " << l << endl;
  }
  return 0;
}
