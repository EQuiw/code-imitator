#include <bits/stdc++.h>
#define fr(a, b, c) for (int a = b, __ = c; a < __; ++a)
#define dbg(x) cerr << ">>> " << x << endl;
#define _ << " , " <<

using namespace std;

set<char> st;
int r, c;
string mat[20];

int main() {
  ios::sync_with_stdio(0);
  int t, cas = 1;
  cin >> t;
  while (t--) {
    cout << "Case #" << cas++ << ":\n";
    st.clear();
    cin >> r >> c;
    fr(i, 0, r) {
      cin >> mat[i];
      fr(j, 0, c) if (mat[i][j] != '?') st.insert(mat[i][j]);
    }
    if (cas == 55) {
      fr(i, 0, r) dbg(mat[i])
    }

    for (auto ch : st) {
      int x1 = 100, y1 = 100, x2 = -1, y2 = -1;
      fr(i, 0, r) {
        fr(j, 0, c) {
          if (mat[i][j] == ch) {
            x1 = min(x1, i);
            x2 = max(x2, i);
            y1 = min(y1, j);
            y2 = max(y2, j);
          }
        }
      }

      fr(i, x1, x2 + 1) fr(j, y1, y2 + 1) mat[i][j] = ch;
    }
    for (auto ch : st) {
      int x1 = 100, y1 = 100, x2 = -1, y2 = -1;
      fr(i, 0, r) {
        fr(j, 0, c) {
          if (mat[i][j] == ch) {
            x1 = min(x1, i);
            x2 = max(x2, i);
            y1 = min(y1, j);
            y2 = max(y2, j);
          }
        }
      }
      bool ok = 1;
      while (y1 > 0 && ok) {
        fr(i, x1, x2 + 1) {
          if (mat[i][y1 - 1] != '?')
            ok = 0;
        }
        if (ok) {
          fr(i, x1, x2 + 1) { mat[i][y1 - 1] = ch; }
          --y1;
        }
      }
      ok = 1;
      while (y2 + 1 < c && ok) {
        fr(i, x1, x2 + 1) {
          if (mat[i][y2 + 1] != '?')
            ok = 0;
        }
        if (ok) {
          fr(i, x1, x2 + 1) { mat[i][y2 + 1] = ch; }
          ++y2;
        }
      }
    }
    for (auto ch : st) {
      int x1 = 100, y1 = 100, x2 = -1, y2 = -1;
      fr(i, 0, r) {
        fr(j, 0, c) {
          if (mat[i][j] == ch) {
            x1 = min(x1, i);
            x2 = max(x2, i);
            y1 = min(y1, j);
            y2 = max(y2, j);
          }
        }
      }
      bool ok = 1;
      while (x2 + 1 < r && ok) {
        fr(j, y1, y2 + 1) {
          if (mat[x2 + 1][j] != '?')
            ok = 0;
        }
        if (ok) {
          fr(j, y1, y2 + 1) { mat[x2 + 1][j] = ch; }
          ++x2;
        }
      }
      ok = 1;
      while (x1 > 0 && ok) {
        fr(j, y1, y2 + 1) {
          if (mat[x1 - 1][j] != '?')
            ok = 0;
        }
        if (ok) {
          fr(j, y1, y2 + 1) { mat[x1 - 1][j] = ch; }
          --x1;
        }
      }
    }

    fr(i, 0, r) cout << mat[i] << endl;
  }
  return 0;
}