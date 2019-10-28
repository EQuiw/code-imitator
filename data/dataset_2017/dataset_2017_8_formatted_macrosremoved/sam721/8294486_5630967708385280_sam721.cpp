#include <bits/stdc++.h>

using namespace std;
int t, n, d;
pair<int, int> horse[1010];
bool can(double speed) { double t = d / speed; }
double T[1010];
int main() {
  scanf("%d", &t);
  for (int c = 1; c <= t; c++) {
    scanf("%d %d", &d, &n);
    for (int i = 0; i < n; i++)
      scanf("%d %d", &horse[i].first, &horse[i].second);
    double speed = 1000000000000000000.0;
    for (int i = 0; i < n; i++) {
      double d1 = (double)(d - horse[i].first);
      double s1 = horse[i].second;
      double s = s1 * d / d1;
      speed = min(speed, s);
    }
    printf("Case #%d: %.10lf\n", c, speed);
  }
  return 0;
}
