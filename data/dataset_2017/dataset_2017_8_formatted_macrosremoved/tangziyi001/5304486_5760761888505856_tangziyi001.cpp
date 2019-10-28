/*
 *
 *	Created by Ziyi Tang
 *
 */

//#include <bits/stdc++.h>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pi;
typedef vector<pi> vpi;
typedef vector<vpi> vvpi;
const int INF = 0x3f3f3f;
const ll INFL = (ll)1E18;
const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

char all[30][30];
int mark[30];
int r, c;
void pr() {
  for (int i = (0); i < (r); i++) {
    for (int j = (0); j < (c); j++) {
      cout << all[i][j];
    }
    cout << endl;
  }
}
void hor(int i, int j, char now) {
  int j1 = j - 1, j2 = j + 1;
  while (j1 >= 0) {
    if (all[i][j1] == '?')
      all[i][j1] = now;
    else
      break;
    j1--;
  }
  while (j2 < c) {
    if (all[i][j2] == '?')
      all[i][j2] = now;
    else
      break;
    j2++;
  }
}
void ver(int i) {
  int i1 = i - 1;
  int i2 = i + 1;
  while (i1 >= 0) {
    if (mark[i1] == 0) {
      for (int j = (0); j < (c); j++) {
        all[i1][j] = all[i][j];
      }
    } else
      break;
    i1--;
  }
  while (i2 < r) {
    if (mark[i2] == 0) {
      for (int j = (0); j < (c); j++) {
        all[i2][j] = all[i][j];
      }
    } else
      break;
    i2++;
  }
}
int main() {
  int test;
  cin >> test;
  for (int t = (1); t < (test + 1); t++) {
    memset(mark, 0, sizeof(mark));
    cin >> r >> c;
    for (int i = (0); i < (r); i++) {
      string line;
      cin >> line;
      for (int j = (0); j < (c); j++) {
        all[i][j] = line[j];
      }
    }
    for (int i = (0); i < (r); i++) {
      for (int j = (0); j < (c); j++) {
        if (all[i][j] != '?') {
          hor(i, j, all[i][j]);
          mark[i] = 1;
        }
      }
    }
    // pr();
    for (int i = (0); i < (r); i++) {
      if (mark[i] == 1) {
        ver(i);
      }
    }
    printf("Case #%d:\n", t);
    pr();
  }
  return 0;
}
