// Hi
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;
struct rect {
  int t, b, l, r;
};
char mat[26][26];
bool checkIfClear(int a, int b, int c, int d, char checker) {
  for (int i = a; i <= b; i++) {
    for (int j = c; j <= d; j++) {
      if (mat[i][j] != '?' && mat[i][j] != checker)
        return false;
    }
  }
  return true;
}
void fillC(int a, int b, int c, int d, char filler) {
  for (int i = a; i <= b; i++) {
    for (int j = c; j <= d; j++) {
      mat[i][j] = filler;
    }
  }
}
void solve(int r, int c) {

  map<char, rect> rs;
  for (int i = 0; i < r; i++) {
    for (int b = 0; b < c; b++) {
      if (mat[i][b] == '?')
        continue;
      char ind = mat[i][b];
      rs[ind].t = i;
      rs[ind].b = i;
      rs[ind].l = b;
      rs[ind].r = b;
    }
  }

  for (int i = 0; i < r; i++) {
    for (int b = 0; b < c; b++) {
      if (mat[i][b] != '?')
        continue;
      for (map<char, rect>::iterator it = rs.begin(); it != rs.end(); ++it) {
        rect check;
        rect cur = it->second;
        check.t = min(cur.t, i);
        check.b = max(cur.b, i);
        check.l = min(cur.l, b);
        check.r = max(cur.r, b);
        if (!checkIfClear(check.t, check.b, check.l, check.r, it->first))
          continue;
        rs[it->first] = check;
        fillC(check.t, check.b, check.l, check.r, it->first);
      }
    }
  }

  for (int i = 0; i < r; i++) {
    for (int b = 0; b < c; b++) {
      cout << mat[i][b];
    }
    cout << endl;
  }
}
int main() {
  ios::sync_with_stdio(false);
  freopen("test.txt", "r", stdin);
  freopen("test1.txt", "w", stdout);
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    int r, c;
    cin >> r >> c;

    for (int j = 0; j < r; j++) {
      for (int b = 0; b < c; b++) {
        cin >> mat[j][b];
      }
    }
    cout << "Case #" << i << ": " << endl;
    solve(r, c);
  }
}
