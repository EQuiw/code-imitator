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

void p2017_1a_a_small() {
  int t, r, c;
  cin >> t;
  int emptyrows[25];
  char s[26][26];
  for (int cs = 1; cs <= t; ++cs) {
    cin >> r >> c;
    memset(emptyrows, 0, sizeof(emptyrows));
    for (int i = 0; i < r; ++i)
      cin >> s[i];
    for (int i = 0; i < r; ++i) {
      int j;
      for (j = 0; j < c && s[i][j] == '?'; ++j)
        ;
      if (j == c)
        emptyrows[i] = 1;
      else {
        int k;
        for (k = 0; k < j; ++k)
          s[i][k] = s[i][j];
        k = j;
        for (; j < c; ++j)
          if (s[i][j] == '?')
            s[i][j] = s[i][k];
          else
            k = j;
      }
    }
    int last = 0;
    while (emptyrows[last] == 1)
      last++;
    for (int i = last; i >= 0; i--)
      for (int j = 0; j < c; ++j)
        s[i][j] = s[last][j];
    for (int i = last; i < r; ++i)
      if (emptyrows[i] == 1)
        for (int j = 0; j < c; ++j)
          s[i][j] = s[last][j];
      else
        last = i;

    cout << "Case #" << cs << ":\n";
    for (int i = 0; i < r; ++i)
      cout << s[i] << "\n";
  }
}

void p2017_1a_b_small() {
  int t, n, p;
  int r[50];
  int q[50][50];
  cin >> t;
  int mins[50], maxs[50];
  for (int c = 1; c <= t; ++c) {
    cin >> n >> p;
    for (int i = 0; i < n; ++i)
      cin >> r[i];
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < p; ++j)
        cin >> q[i][j];
      sort(q[i], q[i] + p);
    }
    int pkg = 0;
    int idx[50] = {0};
    int maxidx = 0;
    while (maxidx < p) {
      int lowerlimit = 0, upperlimit = 0;
      for (int i = 0; i < n; ++i) {
        mins[i] = ceil(10.0 * q[i][idx[i]] / 11 / r[i]);
        maxs[i] = floor(10.0 * q[i][idx[i]] / 9 / r[i]);
        if (mins[i] > mins[lowerlimit])
          lowerlimit = i;
        if (maxs[i] < maxs[upperlimit])
          upperlimit = i;
      }
      if (mins[lowerlimit] <= maxs[upperlimit] && mins[lowerlimit] > 0) {
        pkg++;
        for (int i = 0; i < n; ++i)
          idx[i]++;
        maxidx++;
      } else {
        for (int i = 0; i < n; ++i)
          if (maxs[i] < mins[lowerlimit])
            idx[i]++;
        maxidx++;
      }
    }

    cout << "Case #" << c << ": " << pkg << "\n";
  }
}

void p2017_1a_c_small() {
  int t;
  cin >> t;
  for (int c = 1; c <= t; ++c) {

    cout << "Case #" << c << ": " << c << "\n";
  }
}

int main() {

  p2017_1a_b_small();

  return 0;
}
