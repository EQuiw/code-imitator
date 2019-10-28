#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

double k[1010], s[1010];
double eps = 1.0e-6;
int n;
double d;
bool check(double sp) {
  for (int i = 0; i < n; i++) {
    if (sp <= s[i])
      continue;
    double dif = sp - s[i];
    if (k[i] / dif * sp > d)
      continue;
    return false;
  }
  return true;
}

double bs(double l, double r) {
  // cout << l << " " << r << endl;
  printf("%.6lf %.6lf\n", l, r);
  if (r - l <= eps)
    return l;
  double mid = (double)(l + r) / 2.0;
  if (check(mid)) {
    return bs(mid, r);
  } else
    return bs(l, mid);
}

int main() {
  freopen("A.in", "r", stdin);
  freopen("A.txt", "w", stdout);
  int tt;

  double ans;
  cin >> tt;
  for (int aa = 0; aa < tt; aa++) {
    cin >> d >> n;
    for (int i = 0; i < n; i++) {
      cin >> k[i] >> s[i];
    }

    // ans = bs(0.0,1000000000.0 * 1000000000.0);
    double m = 0.0;
    for (int i = 0; i < n; i++) {
      m = max(m, (d - k[i]) / s[i]);
    }
    ans = d / m;
    cout << "Case #" << aa + 1 << ": ";

    printf("%.6lf\n", ans);
  }

  return 0;
}
