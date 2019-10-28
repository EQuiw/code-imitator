#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 26;

char mat[26][26];

int main() {
  int T;
  scanf("%d", &T);

  for (int t = 1; t <= T; t++) {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        char x;
        scanf(" %c", &x);
        mat[i][j] = x;
      }
    }

    unordered_set<char> used;
    while (true) {
      int best = -1;
      tuple<int, int, int, int, char> info;
      for (int a = 0; a < n; a++) {
        for (int c = 0; c < m; c++) {
          for (int b = a; b < n; b++) {
            unordered_set<char> appears;
            for (int d = c; d < m; d++) {
              for (int i = a; i <= b; i++) {
                if (mat[i][d] != '?')
                  appears.insert(mat[i][d]);
              }

              if (appears.size() == 1) {
                int tmp = (b - a + 1) * (d - c + 1);
                if (used.count(*appears.begin()))
                  continue;
                if (best == -1 || tmp > best) {
                  best = tmp;
                  info = make_tuple(a, b, c, d, *appears.begin());
                }
              }
            }
          }
        }
      }

      if (best == -1)
        break;

      int a, b, c, d;
      char x;
      tie(a, b, c, d, x) = info;

      used.insert(x);

      for (int i = a; i <= b; i++) {
        for (int j = c; j <= d; j++) {
          mat[i][j] = x;
        }
      }
    }

    printf("Case #%d:\n", t);

    bool ok = true;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        printf("%c", mat[i][j]);
        ok = ok && mat[i][j] != '?';
      }
      printf("\n");
    }

    assert(ok);
  }

  return 0;
}
