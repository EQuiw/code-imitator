#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
typedef long long LL;
typedef pair<int, int> PII;
typedef pair<double, int> PDI;
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
priority_queue<PII> q;
int ans[1010];
string s = "RYB";
int main() {
  freopen("B-small-attempt1.in", "r", stdin);
  freopen("output.txt", "w", stdout);
  int t, cas = 1, n, r, o, y, g, b, v;
  cin >> t;
  while (t--) {
    cin >> n >> r >> o >> y >> g >> b >> v;
    //        printf("%d %d %d %d %d %d %d\n",n,r,o,y,g,b,v);
    printf("Case #%d: ", cas++);
    while (!q.empty())
      q.pop();
    if (r)
      q.push({r, 1});
    if (y)
      q.push({y, 2});
    if (b)
      q.push({b, 3});
    int f = 1, cnt = 1;
    while (!q.empty() && f) {
      PII a = q.top(), c;
      q.pop();
      a.first--;
      if (a.second == ans[cnt - 1])
        f = 0;
      ans[cnt++] = a.second;
      if (!q.empty()) {
        c = q.top();
        q.pop();
        c.first--;
        ans[cnt++] = c.second;
      }
      if (a.first)
        q.push(a);
      if (c.first)
        q.push(c);
    }
    if (f && ans[1] == ans[n]) {
      swap(ans[n - 1], ans[n]);
      if (ans[n - 2] == ans[n - 1] || ans[1] == ans[n])
        f = 0;
    }
    if (f)
      for (int i = 1; i <= n; i++)
        cout << s[ans[i] - 1];
    else
      printf("IMPOSSIBLE");
    puts("");
  }
  return 0;
}
