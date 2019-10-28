#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

int main() {
  int nCase;
  cin >> nCase;
  for (int iCase = 1; iCase <= nCase; ++iCase) {
    int d, n;
    cin >> d >> n;
    double t = 0;
    for (int i = 0; i < n; ++i) {
      int x, y;
      cin >> x >> y;
      x = d - x;
      t = max(t, (double)x / (double)y);
    }
    printf("Case #%d: %.6lf\n", iCase, (double)d / (double)t);
  }
}