#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  cin >> t;
  for (int case_num = 1; case_num <= t; ++case_num) {
    int d, n;
    cin >> d >> n;
    double ans_time = 0;
    for (int i = 0; i < n; ++i) {
      int init_pos, speed;
      cin >> init_pos >> speed;
      ans_time = max(ans_time, (d - init_pos) / (speed * 1.0));
    }
    double ans = d / ans_time;
    cout.precision(10);
    cout << fixed << "Case #" << case_num << ": " << ans << "\n";
  }
  return 0;
}
