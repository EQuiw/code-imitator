//============================================================================
// Name        : jam17cpp.cpp
// Author      : Javier Sardinas
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <bits/stdc++.h>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

void p2017_1b_a_small() {
  int t, d, n;
  int k, s;
  cin >> t;
  for (int cas = 1; cas <= t; cas++) {
    cin >> d >> n;
    double t = 0.0, maxt = 0.0;
    for (int i = 0; i < n; ++i) {
      cin >> k >> s;
      t = 1.0 * (d - k) / s;
      if (t > maxt)
        maxt = t;
    }

    printf("Case #%d: %6lf\n", cas, 1.0 * d / maxt);
    // cout << "Case #" << cas << ": " << 1.0*d/maxt << "\n";
  }
}

void p2017_1b_b_small() {
  int t;
  cin >> t;
  for (int cas = 1; cas <= t; cas++) {

    cout << "Case #" << cas << ":\n";
  }
}
void p2017_1b_c_small() {
  int t;
  cin >> t;
  for (int cas = 1; cas <= t; cas++) {

    cout << "Case #" << cas << ":\n";
  }
}

int main() {

  p2017_1b_a_small();

  return 0;
}
