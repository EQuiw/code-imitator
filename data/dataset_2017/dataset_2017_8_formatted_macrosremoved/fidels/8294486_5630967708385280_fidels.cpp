#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

int main() {
  int T, t, D, N, i, K, S;
  double TIME;

  cin >> T;
  for (t = 1; t <= T; t++) {
    cin >> D >> N;

    TIME = 0.0;
    for (i = 0; i < N; i++) {
      cin >> K >> S;
      TIME = max(TIME, (D - K) / ((double)S));
    }
    printf("Case #%d: %.8lf\n", t, D / TIME);
  }

  return 0;
}
