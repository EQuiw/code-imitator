#include <cstdio>
#include <iostream>

using namespace std;

int main() {
  int TT;
  cin >> TT;
  for (int T = 1; T <= TT; ++T) {
    int d, n;
    cin >> d >> n;
    double ans;
    for (int i = 0; i < n; ++i) {
      int k, s;
      cin >> k >> s;
      double speed = double(d) / (double(d - k) / double(s));
      if (i == 0 || speed < ans)
        ans = speed;
    }
    printf("Case #%d: %.9lf\n", T, ans);
  }
}
