#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n, q;
int e[200], s[200];
int d[200][200];
double g[200];

double f(int p, double k, double v) {

  if (p == n)
    return 0;
  if (e[p] >= k && s[p] >= v) {
    if (g[p] > 0)
      return g[p];
    return (g[p] = (double(d[p][p + 1]) / double(s[p]) +
                    f(p + 1, e[p] - d[p][p + 1], s[p])));
  }
  if (e[p] <= k && s[p] <= v)
    return d[p][p + 1] / v + f(p + 1, k - d[p][p + 1], v);
  double ans1 = g[p] > 0 ? g[p]
                         : (double(d[p][p + 1]) / double(s[p]) +
                            f(p + 1, e[p] - d[p][p + 1], s[p]));
  g[p] = ans1;
  double ans2 = -1;
  if (k >= d[p][p + 1])
    ans2 = d[p][p + 1] / v + f(p + 1, k - d[p][p + 1], v);
  if (ans2 == -1)
    return ans1;
  if (ans1 < ans2)
    return ans1;
  return ans2;
}

int main() {
  int TT;
  cin >> TT;
  for (int T = 1; T <= TT; ++T) {
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
      cin >> e[i] >> s[i];
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        cin >> d[i][j];
    memset(g, 0, sizeof(g));
    for (int i = 0; i < q; ++i) {
      int x, y;
      cin >> x >> y;
      double ans = f(x, 0, 0);
      printf("Case #%d: %.9lf\n", T, ans);
    }
  }
}
