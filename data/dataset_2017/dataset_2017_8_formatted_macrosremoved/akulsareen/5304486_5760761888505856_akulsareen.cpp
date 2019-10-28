#include <bits/stdc++.h>
using namespace std;
void dnc(int r1, int r2, int c1, int c2, string inp[]) {
  int ctr = 0;
  char ch;
  for (int i = r1; i <= r2; ++i) {
    for (int j = c1; j <= c2; ++j) {
      if (inp[i][j] != '?') {
        ctr++;
        ch = inp[i][j];
      }
    }
  }
  if (ctr == 1) {
    for (int i = r1; i <= r2; ++i) {
      for (int j = c1; j <= c2; ++j) {
        inp[i][j] = ch;
      }
    }
    return;
  }
  int tctr = 0;
  for (int i = r1; i <= r2; ++i) {
    for (int j = c1; j <= c2; ++j) {
      if (inp[i][j] != '?')
        tctr++;
    }
    if (tctr > 0 && (ctr - tctr) > 0) {
      dnc(r1, i, c1, c2, inp);
      dnc(i + 1, r2, c1, c2, inp);
      return;
    }
  }
  tctr = 0;
  for (int j = c1; j <= c2; ++j) {
    for (int i = r1; i <= r2; ++i) {
      if (inp[i][j] != '?')
        tctr++;
    }
    if (tctr > 0 && (ctr - tctr) > 0) {
      dnc(r1, r2, c1, j, inp);
      dnc(r1, r2, j + 1, c2, inp);
      return;
    }
  }
  assert(false);
}
int main() {
  int t;
  cin >> t;
  for (int case_num = 1; case_num <= t; ++case_num) {
    int r, c;
    cin >> r >> c;
    string inp[r];
    for (int i = 0; i < r; ++i) {
      cin >> inp[i];
    }
    dnc(0, r - 1, 0, c - 1, inp);
    cout << "Case #" << case_num << ":\n";
    for (int i = 0; i < r; ++i) {
      cout << inp[i] << "\n";
    }
  }
  return 0;
}
