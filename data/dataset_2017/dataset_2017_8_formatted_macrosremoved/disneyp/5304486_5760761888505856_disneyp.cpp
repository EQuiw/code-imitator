#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
char s[100][100];
char ans[100][100];
int r, c;
void f(int rr, int cc) {
  int L = cc, R = cc, U = rr, D = rr;
  for (int i = rr - 1; i >= 0; i--) {
    if (ans[i][cc] == '?')
      U = i;
    else
      break;
  }
  for (int i = rr + 1; i < r; i++) {
    if (ans[i][cc] == '?')
      D = i;
    else
      break;
  }

  for (int j = cc - 1; j >= 0; j--) {
    bool ch = true;
    for (int i = U; i <= D; i++) {
      if (ans[i][j] == '?' || ans[i][j] == ans[rr][cc]) {
        continue;
      }
      ch = false;
      break;
    }
    if (ch) {
      L = j;
    } else {
      break;
    }
  }

  for (int j = cc + 1; j < c; j++) {
    bool ch = true;
    for (int i = U; i <= D; i++) {
      if (ans[i][j] == '?' || ans[i][j] == ans[rr][cc]) {
        continue;
      }
      ch = false;
      break;
    }
    if (ch) {
      R = j;
    } else {
      break;
    }
  }
  // cout << s[rr][cc] << " " << L << R << U << D << endl;

  for (int i = U; i <= D; i++)
    for (int j = L; j <= R; j++)
      ans[i][j] = s[rr][cc];
}

int main() {
  freopen("A.in", "r", stdin);
  freopen("A.txt", "w", stdout);
  int t;
  cin >> t;
  for (int aa = 0; aa < t; aa++) {
    cin >> r >> c;
    for (int i = 0; i < r; i++)
      scanf("%s", s[i]);
    for (int i = 0; i < r; i++)
      for (int j = 0; j < c; j++)
        ans[i][j] = s[i][j];

    for (int j = 0; j < c; j++) {
      for (int i = 0; i < r; i++) {
        if (s[i][j] == '?')
          continue;
        f(i, j);
      }
    }

    cout << "Case #" << aa + 1 << ":" << endl;
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++)
        cout << ans[i][j];
      cout << endl;
    }
  }
}
