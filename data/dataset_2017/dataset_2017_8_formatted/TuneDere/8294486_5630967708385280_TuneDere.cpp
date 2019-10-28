#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  int casen;
  cin >> casen;
  for (int casex = 1; casex <= casen; casex++) {
    int d, n;
    cin >> d >> n;
    double kk, ss;
    double maxt = 0;
    for (int i = 0; i < n; i++) {
      cin >> kk >> ss;
      double t = (d - kk) / ss;
      maxt = max(maxt, t);
    }
    cout << "Case #" << casex << ": ";
    printf("%.6f\n", d / maxt);
  }
  return 0;
}
