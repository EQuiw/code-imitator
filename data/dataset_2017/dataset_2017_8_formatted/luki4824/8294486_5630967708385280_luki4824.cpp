#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#define MAX_N 1001
#define INF 1000000000
using namespace std;
int n, d;
pair<double, double> horses[MAX_N];
void clear() {}
void solve() {
  double res = d / ((d - horses[0].first) / horses[0].second);
  for (int i = 0; i < n; ++i) {
    if (horses[i].first < d)
      res = min(res, d / ((d - horses[i].first) / horses[i].second));
  }
  printf("%0.6lf\n", res);
}
void input() {
  cin >> d >> n;
  double a, b;
  for (int i = 0; i < n; ++i) {
    cin >> a >> b;
    horses[i].first = a;
    horses[i].second = b;
  }
  sort(horses, horses + n);
}
int main() {
  int t, m, n;
  cin >> t;
  for (int k = 1; k <= t; ++k) {
    clear();
    input();
    printf("Case #%d: ", k);
    solve();
  }
}