#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
typedef pair<int, int> P2;
template <class A, class B> inline bool mina(A &first, B second) {
  return (first > second) ? (first = second, 1) : 0;
}
template <class A, class B> inline bool maxa(A &first, B second) {
  return (first < second) ? (first = second, 1) : 0;
}

const int MAXN = 25;

string in[MAXN];
string ans[MAXN];

void solve() {
  int R, C;
  cin >> R >> C;
  for (int(i) = 0; (i) < (R); ++(i)) {
    cin >> in[i];
    ans[i] = in[i];
  }
  for (int(i) = 0; (i) < (R); ++(i)) {
    for (int(j) = 0; (j) < (C); ++(j)) {
      if (in[i][j] != '?') {
        //                int rr = C - 1;
        //                int ll = 0;
        int bb = R - 1;
        for (int i2 = i + 1; i2 < R; i2++) {
          for (int j2 = j; j2 < C; j2++) {
            if (in[i2][j2] != '?' && in[i2][j2] != in[i][j]) {
              bb = min(bb, i2 - 1);
            }
          }
        }
        int rr = C - 1;
        for (int j2 = j + 1; j2 < C; j2++) {
          for (int i2 = 0; i2 < R; i2++) {
            if (in[i2][j2] != '?' && in[i2][j2] != in[i][j]) {
              rr = min(rr, j2 - 1);
            }
          }
        }
        for (int i2 = i; i2 <= bb; i2++) {
          for (int j2 = j; j2 <= rr; j2++) {
            ans[i2][j2] = in[i][j];
          }
        }
      }
    }
  }
  for (int(i) = 0; (i) < (R); ++(i)) {
    for (int(j) = 0; (j) < (C); ++(j)) {
      if (i && ans[i - 1][j] != '?' && ans[i][j] == '?') {
        ans[i][j] = ans[i - 1][j];
      }
    }
  }
  // REP(i, R)
  //     cout << in[i] << endl;
  for (int(i) = 0; (i) < (R); ++(i)) {
    for (int(j) = 0; (j) < (C); ++(j)) {
      if (ans[i][j] == '?') {
        char color = '?';
        for (int j2 = j; j2 < C && color == '?'; j2++) {
          for (int i2 = i; i2 < R && color == '?'; i2++) {
            if (ans[i2][j2] != '?') {
              color = ans[i2][j2];
            }
          }
        }
        ans[i][j] = color;
      }
    }
  }
  for (int(i) = 0; (i) < (R); ++(i))
    cout << ans[i] << endl;
}

int main() {
  int test;
  cin >> test;
  for (int(tt) = 0; (tt) < (test); ++(tt)) {
    cout << "Case #" << (tt + 1) << ":\n";
    solve();
  }

  return 0;
}
