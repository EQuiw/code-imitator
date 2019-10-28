#include <cstdio>
#include <iostream>
using namespace std;

int main() {
  int T;
  cin >> T;
  for (int test = 0; test < T; ++test) {
    int D, N;
    cin >> D >> N;
    double ans = -1;
    for (int i = 0; i < N; ++i) {
      int K, S;
      cin >> K >> S;
      double time = 1.0 * (D - K) / S;

      double speed = D / time;
      if (speed < ans || i == 0) {
        ans = speed;
      }
    }
    cout << "Case #" << test + 1 << ": ";
    //                cout << ans << endl;
    printf("%.6f\n", ans);
  }
  return 0;
}
