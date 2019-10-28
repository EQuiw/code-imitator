#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int main() {
  int T;
  cin >> T;
  for (int I = 1; I <= T; I++) {
    int n;
    double d;
    cin >> d >> n;
    vector<double> pos(n);
    vector<double> vel(n);
    for (int i = 0; i < n; i++)
      cin >> pos[i] >> vel[i];
    long double iz = 0;
    long double der = 1e108;
    long double med = (iz + der) / 2.0;
    while (der - iz > 1e-6) {
      med = (iz + der) / 2.0;
      long double t = d / med;
      for (int i = 0; i < n; i++) {
        if ((d - pos[i]) / vel[i] > t) {
          der = med;
          goto aaa;
        }
      }
      iz = med;
    aaa:;
      // cout << der-iz << endl;
    }
    printf("Case #%d: %.6Lf\n", I, med);
  }
}
