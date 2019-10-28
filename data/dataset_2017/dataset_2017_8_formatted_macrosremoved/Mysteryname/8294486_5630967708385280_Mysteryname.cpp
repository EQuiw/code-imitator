
/*
Contest: Google Code Jam 2017 [Round 1B]
*/

#include <algorithm>
#include <stdio.h>
using namespace std;

int n;
double dst;

double startPoint[1111];
double speed[1111];

double getHorse(int idx) {
  // printf("GetHorse #%d\n",idx+1);
  double distanceLeft = dst - startPoint[idx];
  // printf("DistanceLeft: %.3f\n",distanceLeft);
  double timeUsed = distanceLeft / speed[idx];
  // printf("Time used: %.3f\n",timeUsed);
  double allow = dst / timeUsed;
  // printf("Allow: %.3f\n",allow);
  return dst / timeUsed;
}

double solve() {
  int d;
  scanf("%d%d", &d, &n);
  dst = d;
  for (int i = 0; i < n; i++) {
    int k, s;
    scanf("%d%d", &k, &s);
    startPoint[i] = k;
    speed[i] = s;
  }
  double worst = 99999999999999.999;
  for (int i = 0; i < n; i++) {
    double thisTime = getHorse(i);
    worst = min(worst, thisTime);
  }
  return worst;
}

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-Small.txt", "w", stdout);
  int tc;
  scanf("%d", &tc);
  for (int t = 1; t <= tc; t++) {
    printf("Case #%d: ", t);
    double ans = solve();
    printf("%.9f\n", ans);
  }
  return 0;
}
