#include <iostream>
#include <stdio.h>
#include <string.h>

int D, N;
int K[1005];
int S[1005];
void solve(void);

int main(int argc, const char *argv[]) {
  freopen("/Volumes/4HOPE/Dropbox/17Todai/CodeJam/R1B-2017-A/in.txt", "r",
          stdin);
  freopen("/Volumes/4HOPE/Dropbox/17Todai/CodeJam/R1B-2017-A/out.txt", "w",
          stdout);
  int t;
  scanf("%d", &t);
  for (int cnt = 0; cnt < t; cnt++) {
    scanf("%d %d", &D, &N);
    for (int cnt = 0; cnt < N; cnt++) {
      scanf("%d %d", &K[cnt], &S[cnt]);
    }
    printf("Case #%d: ", cnt + 1);
    solve();
  }
  return 0;
}

void solve(void) {
  double minSpeed = (double)S[0] * (double)D / 1 + 1; // 100000000000000;
  for (int cnt = 0; cnt < N; cnt++) {
    double nowSpeed = ((double)S[cnt] * (double)D) / (double)(D - K[cnt]);
    if (nowSpeed <= minSpeed) {
      minSpeed = nowSpeed;
    }
  }
  printf("%.6f\n", minSpeed);
}
