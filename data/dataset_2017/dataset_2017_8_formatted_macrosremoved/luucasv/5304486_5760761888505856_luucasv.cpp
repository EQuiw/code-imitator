#include <bits/stdc++.h>

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
    for (int i = 0, __ = r; i < __; ++i) {
      cin >> mat[i];
      for (int j = 0, __ = c; j < __; ++j)
        if (mat[i][j] != '?')
          st.insert(mat[i][j]);
    }
    if (cas == 55) {
      for (int i = 0, __ = r; i < __; ++i)
        cerr << ">>> " << mat[i] << endl;
    }

    for (auto ch : st) {
      int x1 = 100, y1 = 100, x2 = -1, y2 = -1;
      for (int i = 0, __ = r; i < __; ++i) {
        for (int j = 0, __ = c; j < __; ++j) {
          if (mat[i][j] == ch) {
            x1 = min(x1, i);
            x2 = max(x2, i);
            y1 = min(y1, j);
            y2 = max(y2, j);
          }
        }
      }

      for (int i = x1, __ = x2 + 1; i < __; ++i)
        for (int j = y1, __ = y2 + 1; j < __; ++j)
          mat[i][j] = ch;
    }
    for (auto ch : st) {
      int x1 = 100, y1 = 100, x2 = -1, y2 = -1;
      for (int i = 0, __ = r; i < __; ++i) {
        for (int j = 0, __ = c; j < __; ++j) {
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
        for (int i = x1, __ = x2 + 1; i < __; ++i) {
          if (mat[i][y1 - 1] != '?')
            ok = 0;
        }
        if (ok) {
          for (int i = x1, __ = x2 + 1; i < __; ++i) {
            mat[i][y1 - 1] = ch;
          }
          --y1;
        }
      }
      ok = 1;
      while (y2 + 1 < c && ok) {
        for (int i = x1, __ = x2 + 1; i < __; ++i) {
          if (mat[i][y2 + 1] != '?')
            ok = 0;
        }
        if (ok) {
          for (int i = x1, __ = x2 + 1; i < __; ++i) {
            mat[i][y2 + 1] = ch;
          }
          ++y2;
        }
      }
    }
    for (auto ch : st) {
      int x1 = 100, y1 = 100, x2 = -1, y2 = -1;
      for (int i = 0, __ = r; i < __; ++i) {
        for (int j = 0, __ = c; j < __; ++j) {
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
        for (int j = y1, __ = y2 + 1; j < __; ++j) {
          if (mat[x2 + 1][j] != '?')
            ok = 0;
        }
        if (ok) {
          for (int j = y1, __ = y2 + 1; j < __; ++j) {
            mat[x2 + 1][j] = ch;
          }
          ++x2;
        }
      }
      ok = 1;
      while (x1 > 0 && ok) {
        for (int j = y1, __ = y2 + 1; j < __; ++j) {
          if (mat[x1 - 1][j] != '?')
            ok = 0;
        }
        if (ok) {
          for (int j = y1, __ = y2 + 1; j < __; ++j) {
            mat[x1 - 1][j] = ch;
          }
          --x1;
        }
      }
    }

    for (int i = 0, __ = r; i < __; ++i)
      cout << mat[i] << endl;
  }
  return 0;
}
