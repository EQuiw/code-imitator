//
//  main2017.cpp
//  Codejam2015
//
//  Created by stoness on 17/4/8.
//  Copyright © 2017年 sts. All rights reserved.
//

#include <algorithm>
#include <bitset>
#include <cmath>
#include <iostream>
#include <list>

#define check_bit(var, pos) ((var) & (1 << (pos)))

using namespace std;

int p1() {
  int r, c, i, j;
  char csh[32][32] = {0};
  cin >> r >> c;
  for (i = 0; i < r; ++i)
    for (int j = 0; j < c; ++j)
      cin >> csh[i][j];
  for (i = 0; i < r; ++i) {
    char f = '?';
    for (j = 0; j < c; ++j) {
      if (csh[i][j] != '?') {
        f = csh[i][j];
        break;
      }
    }
    if (f == '?') {
      continue;
    }
    for (j = 0; j < c; ++j) {
      if (csh[i][j] != '?')
        f = csh[i][j];
      else
        csh[i][j] = f;
    }
    for (int k = i - 1; k >= 0; --k) {
      if (csh[k][0] == '?')
        memcpy(csh[k], csh[i], c);
      else
        break;
    }
  }
  for (int k = 1; k < r; ++k)
    if (csh[k][0] == '?')
      memcpy(csh[k], csh[k - 1], c);
  for (i = 0; i < r; ++i) {
    for (j = 0; j < c; ++j)
      cout << csh[i][j];
    cout << endl;
  }
  return 0;
}

bool p2pack(int f[60][60], int r[], int t[], int mi, int ma, int n, int p,
            int ro) {
  int a, b, i;
  if (ro > n)
    return true;
  for (i = 1; i <= p; ++i) {
    if (f[ro][i] == 0)
      continue;
    a = ceil(f[ro][i] / 1.1 / r[ro]);
    b = floor(f[ro][i] / 0.9 / r[ro]);
    if (a > b)
      continue;
    if (b < mi)
      continue;
    if (ma < a)
      return false;
    mi = max(mi, a);
    ma = min(ma, b);
    if (ro == n) {
      t[ro] = i;
      return true;
    } else if (!p2pack(f, r, t, mi, ma, n, p, ro + 1))
      continue;
    else {
      t[ro] = i;
      return true;
    }
  }
  return false;
}
int p2() {
  int res(0), i, j;
  int f[60][60] = {0};
  int n, p, r[60] = {0}, t[60];
  cin >> n >> p;
  for (i = 1; i <= n; ++i)
    cin >> r[i];
  for (i = 1; i <= n; ++i) {
    t[i] = 1;
    for (j = 1; j <= p; ++j)
      cin >> f[i][j];
    sort(f[i] + 1, f[i] + 1 + p);
  }
  int mi = 1, ma = 1000001;
  for (i = 1; i <= p; ++i) {
    mi = ceil(f[1][i] / 1.1 / r[1]);
    ma = floor(f[1][i] / 0.9 / r[1]);
    if (ma < 1)
      continue;
    if (mi > ma)
      continue;
    if (p2pack(f, r, t, mi, ma, n, p, 2)) {
      res++;
      for (j = 2; j <= n; ++j)
        f[j][t[j]] = 0;
    }
  }
  return res;
}

int main(int argc, const char *argv[]) {
  int T(0);
  int r1(0);
  cin >> T;
  for (int i = 0; i < T; ++i) {
    r1 = p2();
    cout << "Case #" << i + 1 << ": " << r1 << endl; // p1();
    // if (r1<0) cout<<"IMPOSSIBLE"<<endl;
    // else      cout<<r1<<endl;
  }
  return 0;
}
