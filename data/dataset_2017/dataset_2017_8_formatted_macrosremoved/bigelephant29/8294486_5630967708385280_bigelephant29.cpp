#include <algorithm>
#include <cstdio>
#include <cstdlib>
using namespace std;
int main() {
  int TN;
  scanf("%d", &TN);
  for (int casen = 1; casen <= TN; casen++) {
    printf("Case #%d: ", casen);
    double d, time = 0;
    int n;
    scanf("%lf %d", &d, &n);
    for (int i = 0; i < n; i++) {
      double pos, spd;
      scanf("%lf %lf", &pos, &spd);
      time = max(time, (d - pos) / spd);
    }
    printf("%.9f\n", d / time);
  }
  return 0;
}
