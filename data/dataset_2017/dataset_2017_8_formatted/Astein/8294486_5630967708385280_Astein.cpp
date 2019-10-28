#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-small-attempt0.out", "w", stdout);

  int T;
  scanf("%d", &T);
  for (int cn = 1; cn <= T; ++cn) {
    int D, N;
    scanf("%d%d", &D, &N);
    double last_time = 0;
    for (int i = 0; i < N; ++i) {
      int K, S;
      scanf("%d%d", &K, &S);
      double cur = (D - K) * 1.0 / S;
      last_time = max(last_time, cur);
    }
    printf("Case #%d: %.10lf\n", cn, D * 1.0 / last_time);
  }
}