#include <algorithm>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

const double eps = 1e-8;
const double pi = acos(-1.0);

const int N = 1005;

double k[N];
double s[N];

bool check(double mid, int n, double d);

int main() {
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int T;
  cin >> T;

  for (int cas = 1; cas <= T; cas++) {
    double d;
    int n;
    cin >> d >> n;
    for (int i = 1; i <= n; i++) {
      cin >> k[i] >> s[i];
    }

    double ti = 0;
    for (int i = 1; i <= n; i++) {
      double way = d - k[i];
      double time = way / s[i];
      ti = max(ti, time);
    }

    printf("Case #%d: %.8f\n", cas, d / ti);
  }
  return 0;
}
