#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pt;
const int base = 1000000007;
const int maxn = 100002;
const double esp = 1e-9;

int n, D;
double res;
pt a[maxn];

bool ok(double v) {
  int i, j;
  for (i = 1; i <= n; i++)
    if (a[i].second < v - esp) {
      double t = double(a[i].first) / (v - a[i].second);
      double first = v * t;
      if (first < double(D) - esp)
        return false;
    }
  return true;
}

void solve(int test) {
  int i, j, k, u, v;
  double l, r, first;

  scanf("%d%d", &D, &n);
  res = base;
  for (i = 1; i <= n; i++) {
    scanf("%d%d", &a[i].first, &a[i].second);
    res = min(res, double(a[i].second));
  }

  /* l = 0; r = 1000000000;
   while (abs(r-l) / res > esp) {
       x = (l+r) / 2;
       if (ok(x)) {res = x; l = x+esp;}
       else r = x-esp;
   }*/
  sort(a + 1, a + n + 1);
  double slowest = esp;
  for (i = n; i >= 1; i--) {
    slowest = max(slowest, double(D - a[i].first) / a[i].second);
  }
  res = D / slowest;

  printf("Case #%d: %.6lf\n", test, res);
}

int main() {
  int i, t;
  freopen("A.in", "r", stdin);
  freopen("A1.out", "w", stdout);

  scanf("%d", &t);
  for (i = 1; i <= t; i++)
    solve(i);

  return 0;
}
