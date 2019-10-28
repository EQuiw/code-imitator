#include <iostream>
#include <stdio.h>
using namespace std;

struct H {
  long long int pos, speed;
};
int T;
long long int D;
int N;
H h[1001];

bool order(const H &x, const H &y) {
  if (x.pos < y.pos)
    return true;
  else
    return false;
}
int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int t;
  int i;

  scanf("%d", &T);
  for (t = 1; t <= T; t++) {
    scanf("%lld %d", &D, &N);
    for (i = 0; i < N; i++)
      scanf("%lld %lld", &h[i].pos, &h[i].speed);

    double max = 0;
    for (i = 0; i < N; i++) {
      if (max < (double)(D - h[i].pos) / (double)h[i].speed)
        max = (double)(D - h[i].pos) / (double)h[i].speed;
    }
    printf("Case #%d: ", t);
    printf("%lf\n", (double)D / max);
  }
  return 0;
}
