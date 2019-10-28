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
#define REP(i, s, t) for (int i = (s); i < (t); i++)
#define FILL(x, v) memset(x, v, sizeof(x))
#define MAXN 30
#define MOD 1000000007

char all[MAXN][MAXN];
int mark[MAXN];
int r, c;
void pr() {
  REP(i, 0, r) {
    REP(j, 0, c) { cout << all[i][j]; }
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
      REP(j, 0, c) { all[i1][j] = all[i][j]; }
    } else
      break;
    i1--;
  }
  while (i2 < r) {
    if (mark[i2] == 0) {
      REP(j, 0, c) { all[i2][j] = all[i][j]; }
    } else
      break;
    i2++;
  }
}
int main() {
  int test;
  cin >> test;
  REP(t, 1, test + 1) {
    FILL(mark, 0);
    cin >> r >> c;
    REP(i, 0, r) {
      string line;
      cin >> line;
      REP(j, 0, c) { all[i][j] = line[j]; }
    }
    REP(i, 0, r) {
      REP(j, 0, c) {
        if (all[i][j] != '?') {
          hor(i, j, all[i][j]);
          mark[i] = 1;
        }
      }
    }
    // pr();
    REP(i, 0, r) {
      if (mark[i] == 1) {
        ver(i);
      }
    }
    printf("Case #%d:\n", t);
    pr();
  }
  return 0;
}