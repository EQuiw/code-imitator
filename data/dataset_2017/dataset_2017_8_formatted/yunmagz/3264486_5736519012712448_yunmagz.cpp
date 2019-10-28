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
int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);
  int t, k, cas = 1;
  string s;
  cin >> t;
  while (t--) {
    cin >> s >> k;
    int n = SZ(s);
    for (int i = 0; i < n; i++)
      a[i] = (s[i] == '+');
    int f = 1, ans = 0;
    for (int i = 0; i < n && f; i++) {
      if (i + k <= n) {
        if (!a[i]) {
          ans++;
          for (int j = i; j < i + k; j++)
            a[j] ^= 1;
        }
      } else if (!a[i])
        f = 0;
    }
    printf("Case #%d: ", cas++);
    if (f)
      cout << ans << endl;
    else
      puts("IMPOSSIBLE");
  }
  return 0;
}
