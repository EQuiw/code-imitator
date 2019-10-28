#include <bits/stdc++.h>
using namespace std;

struct Re {
  int idx, line, row;
  Re() {}
  Re(int idx, int line, int row) : idx(idx), line(line), row(row) {}
  bool operator<(const Re &re) const {
    if (row != re.row)
      return row < re.row;
    return line < re.line;
  }
} re[33];

char mat[33][33];
vector<pair<int, int>> sav[33];

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-small-attempt0.out", "w", stdout);

  int test;
  scanf("%d", &test);
  for (int _ = 1; _ <= test; _++) {
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; i++) {
      scanf("%s", mat[i]);
      sav[i].clear();
    }

    int totre = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (mat[i][j] != '?') {
          sav[i].push_back({mat[i][j], j});
          re[totre++] = Re(mat[i][j] - 'A', i, j);
        }
      }
    }

    int ed[33];
    char lab[33];

    int mxline = 0;
    for (int i = 0, preline = 0; i < n; i++) {
      if (sav[i].size()) {
        mxline = max(mxline, i);
        for (int k = 0; k < sav[i].size(); k++) {
          ed[k] = sav[i][k].second;
          lab[k] = sav[i][k].first;
        }
        ed[sav[i].size() - 1] = m - 1;

        for (int k = 0, pre = 0; k < sav[i].size(); k++) {
          for (int ii = preline; ii <= i; ii++) {
            for (int j = pre; j <= ed[k]; j++) {
              mat[ii][j] = lab[k];
            }
          }

          pre = ed[k] + 1;
        }
        preline = i + 1;
      }
    }

    for (int i = mxline + 1; i < n; i++) {
      for (int j = 0; j < m; j++) {
        mat[i][j] = mat[mxline][j];
      }
    }

    printf("Case #%d:\n", _);
    for (int i = 0; i < n; i++) {
      puts(mat[i]);
    }
  }
  return 0;
}
