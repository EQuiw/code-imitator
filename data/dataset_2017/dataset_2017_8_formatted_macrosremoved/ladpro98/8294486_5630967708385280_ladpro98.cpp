#include <bits/stdc++.h>

using namespace std;

int main() {
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; ++tc) {
    long long D;
    int n;
    cin >> D >> n;
    vector<long long> pos(n), speed(n);
    for (int i = 0; i < n; ++i) {
      cin >> pos[i] >> speed[i];
    }
    // time_catch = (pos2 - pos1) / (v1 - v2)
    // time_catch <= (D - pos2) / v2
    double answer = 1e18;
    for (int i = 0; i < n; ++i) {
      double time_catch = 1.0 * (D - pos[i]) / speed[i];
      double max_speed = pos[i] / time_catch + speed[i];
      answer = min(answer, max_speed);
    }
    assert(answer < 1e17);
    cout << setprecision(6) << fixed << "Case #" << tc << ": " << answer
         << endl;
  }
  return 0;
}
