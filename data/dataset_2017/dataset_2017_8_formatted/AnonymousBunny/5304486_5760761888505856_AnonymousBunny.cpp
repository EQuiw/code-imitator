#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define mp make_pair
#define F first
#define S second
const int mod = 1e9 + 7;
#define maxn 30

char a[maxn][maxn];
int done[maxn][maxn];
int R, C;
void fix(int tt, int l, int r, char c) {
  for (int i = tt; i >= 1; i--) {
    if (a[i][l] != '?')
      break;
    for (int j = l; j <= r; j++)
      a[i][j] = c;
  }
}

void fixdown(int tt) {
  for (int i = tt; i < R; i++) {
    for (int j = 1; j <= C; j++)
      a[i + 1][j] = a[i][j];
  }
}

void solve(int ind) {
  int r, c;
  cin >> r >> c;
  R = r;
  C = c;
  for (int i = 1; i <= r; i++) {
    for (int j = 1; j <= c; j++) {
      cin >> a[i][j];
      done[i][j] = 0;
    }
  }
  for (int i = 1; i <= r; i++) {
    for (int j = 1; j <= c; j++) {
      if (a[i][j] == '?')
        continue;
      int lt = j, rt = j;
      for (int k = j - 1; k >= 1; k--) {
        if (a[i][k] == '?') {
          a[i][k] = a[i][j];
          lt = k;
        } else
          break;
      }
      for (int k = j + 1; k <= C; k++) {
        if (a[i][k] == '?') {
          a[i][k] = a[i][j];
          rt = k;
        } else
          break;
      }
      fix(i - 1, lt, rt, a[i][j]);
    }
  }
  for (int i = r; i >= 1; i--) {
    if (a[i][1] != '?') {
      fixdown(i);
      break;
    }
  }
  cout << "Case #" << ind << ": " << endl;
  for (int i = 1; i <= r; i++) {
    for (int j = 1; j <= c; j++)
      cout << a[i][j];
    cout << endl;
  }
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++)
    solve(i);
  return 0;
}