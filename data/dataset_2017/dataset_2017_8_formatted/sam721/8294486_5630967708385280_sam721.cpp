#include <bits/stdc++.h>
#define LL long long
#define VI vector<int>
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define INF 0x3f3f3f3f
using namespace std;
int t, n, d;
pii horse[1010];
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