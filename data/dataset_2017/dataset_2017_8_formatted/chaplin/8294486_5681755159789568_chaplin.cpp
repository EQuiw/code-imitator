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
  int t, n, r, g, b, y, o, v;
  cin >> t;
  for (int cas = 1; cas <= t; cas++) {
    cin >> n >> r >> o >> y >> g >> b >> v;
    if (r + y < b || r + b < y || y + b < r)
      cout << "Case #" << cas << ": IMPOSSIBLE\n";
    else {
      int x1, x2, x3;
      char c1, c2, c3;
      if (r > y) {
        if (r > b) {
          x1 = r, c1 = 'R';
          if (y > b)
            x2 = y, c2 = 'Y', x3 = b, c3 = 'B';
          else
            x3 = y, c3 = 'Y', x2 = b, c2 = 'B';
        } else {
          x1 = b, c1 = 'B', x2 = r, c2 = 'R', x3 = y, c3 = 'Y';
        }
      } else {
        if (y > b) {
          x1 = y, c1 = 'Y';
          if (r > b)
            x2 = r, c2 = 'R', x3 = b, c3 = 'B';
          else
            x3 = r, c3 = 'R', x2 = b, c2 = 'B';
        } else
          x1 = b, c1 = 'B', x2 = y, c2 = 'Y', x3 = r, c3 = 'R';
      }

      cout << "Case #" << cas << ": ";
      char last = c1;
      while (x1 || x2 || x3) {
        cout << last;
        if (last == c1) {
          x1--;
          last = x2 >= x3 ? c2 : c3;
        } else if (last == c2) {
          x2--;
          last = x1 >= x3 ? c1 : c3;
        } else {
          x3--;
          last = x1 >= x2 ? c1 : c2;
        }
      }
      cout << "\n";
    }
  }
}

void p2017_1b_b_large() {
  int t;
  cin >> t;
  for (int cas = 1; cas <= t; cas++) {

    cout << "Case #" << cas << ":\n";
  }
}

void p2017_1b_c_small() {
  int t, n, q;
  int e[100], s[100], d[100][100];
  int u[100], v[100];
  cin >> t;
  long long inf = 10000000000000000;
  for (int cas = 1; cas <= t; cas++) {
    cin >> n >> q;
    for (int i = 0; i < n; ++i)
      cin >> e[i] >> s[i];
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        cin >> d[i][j];
    for (int i = 0; i < q; ++i)
      cin >> u[i] >> v[i];

    long long D[100][100];
    for (int i = 0; i < n; ++i)
      for (int j = i + 1; j < n; ++j)
        D[i][j] = d[i][j];
    for (int i = 0; i < n; ++i)
      for (int j = i + 2; j < n; ++j)
        D[i][j] = D[i][j - 1] + d[j - 1][j];

    double dp[100][100];
    for (int i = 1; i < n; ++i)
      dp[i][0] = d[0][i] <= e[0] ? 1.0 * D[0][i] / s[0] : inf;
    double m = dp[1][0];
    for (int j = 1; j < n; ++j) {
      for (int i = j + 1; i < n; ++i) {
        dp[i][j] = D[j][i] <= e[j] ? 1.0 * D[j][i] / s[j] + m : inf;
      }
      m = inf;
      for (int k = 0; k < j; ++k)
        if (dp[j][k] < m)
          m = dp[j][k];
    }

    printf("Case #%d: %6lf\n", cas, m);
    // cout << "Case #" << cas << ": " << m << "\n";
  }
}

void p2017_1b_c_large() {
  int t, n, q;
  int e[100], s[100], d[100][100];
  int u[100], v[100];
  cin >> t;
  for (int cas = 1; cas <= t; cas++) {
    cin >> n >> q;
    for (int i = 0; i < n; ++i)
      cin >> e[i] >> s[i];
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        cin >> d[i][j];
    for (int i = 0; i < q; ++i)
      cin >> u[i] >> v[i];
    cout << "Case #" << cas << ":\n";
  }
}

int main() {

  p2017_1b_c_small();

  return 0;
}
