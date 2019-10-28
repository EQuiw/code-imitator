#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int t;
  cin >> t;

  for (int z = 1; z <= t; z++) {
    ll d;
    int n;
    cin >> d >> n;
    double tmin = 0.0;
    for (int i = 0; i < n; i++) {
      ll k, speed;
      cin >> k >> speed;
      ll distrem = d - k;
      double timerem = ((1.0) * distrem);
      timerem = timerem / ((double)speed);
      if (timerem > tmin) {
        tmin = timerem;
      }
    }
    double speed = (double)d / tmin;
    printf("Case #%d: %.6f\n", z, speed);
  }
}
