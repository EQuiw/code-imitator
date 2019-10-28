#include <bits/stdc++.h>

char str[26][26];

int main() {
  int tc;
  scanf("%d", &tc);
  int T = 0;
  while (tc--) {
    int r, c;
    scanf("%d%d", &r, &c);
    std::map<char, int> mx, Mx, my, My;
    for (int i = 0; i < r; i++) {
      scanf("%s", str[i]);
      for (int j = 0; j < c; j++) {
        if (mx.count(str[i][j])) {
          mx[str[i][j]] = std::min(mx[str[i][j]], i);
        } else {
          mx[str[i][j]] = i;
        }
        if (Mx.count(str[i][j])) {
          Mx[str[i][j]] = std::max(Mx[str[i][j]], i);
        } else {
          Mx[str[i][j]] = i;
        }
        if (my.count(str[i][j])) {
          my[str[i][j]] = std::min(my[str[i][j]], j);
        } else {
          my[str[i][j]] = j;
        }
        if (My.count(str[i][j])) {
          My[str[i][j]] = std::min(My[str[i][j]], j);
        } else {
          My[str[i][j]] = j;
        }
      }
    }
    for (auto p : mx) {
      char ch = p.first;
      if (ch == '?')
        continue;
      for (int i = mx[ch]; i <= Mx[ch]; i++) {
        for (int j = my[ch]; j <= My[ch]; j++) {
          str[i][j] = ch;
        }
      }
    }

    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (str[i][j] != '?') {
          for (int k = 1; i + k < r; k++) {
            bool flag = false;
            for (int p = my[str[i][j]]; p <= My[str[i][j]]; p++) {
              if (str[i + k][p] != '?') {
                flag = true;
                break;
              }
            }
            if (flag)
              break;
            for (int p = my[str[i][j]]; p <= My[str[i][j]]; p++) {
              str[i + k][p] = str[i][j];
            }
          }
        }
      }
    }
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (mx.count(str[i][j])) {
          mx[str[i][j]] = std::min(mx[str[i][j]], i);
        } else {
          mx[str[i][j]] = i;
        }
        if (Mx.count(str[i][j])) {
          Mx[str[i][j]] = std::max(Mx[str[i][j]], i);
        } else {
          Mx[str[i][j]] = i;
        }
        if (my.count(str[i][j])) {
          my[str[i][j]] = std::min(my[str[i][j]], j);
        } else {
          my[str[i][j]] = j;
        }
        if (My.count(str[i][j])) {
          My[str[i][j]] = std::min(My[str[i][j]], j);
        } else {
          My[str[i][j]] = j;
        }
      }
    }

    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (str[i][j] != '?') {
          for (int k = -1; i + k >= 0; k--) {
            bool flag = false;
            for (int p = my[str[i][j]]; p <= My[str[i][j]]; p++) {
              if (str[i + k][p] != '?') {
                flag = true;
                break;
              }
            }
            if (flag)
              break;
            for (int p = my[str[i][j]]; p <= My[str[i][j]]; p++) {
              str[i + k][p] = str[i][j];
            }
          }
        }
      }
    }
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (mx.count(str[i][j])) {
          mx[str[i][j]] = std::min(mx[str[i][j]], i);
        } else {
          mx[str[i][j]] = i;
        }
        if (Mx.count(str[i][j])) {
          Mx[str[i][j]] = std::max(Mx[str[i][j]], i);
        } else {
          Mx[str[i][j]] = i;
        }
        if (my.count(str[i][j])) {
          my[str[i][j]] = std::min(my[str[i][j]], j);
        } else {
          my[str[i][j]] = j;
        }
        if (My.count(str[i][j])) {
          My[str[i][j]] = std::min(My[str[i][j]], j);
        } else {
          My[str[i][j]] = j;
        }
      }
    }
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (str[i][j] != '?') {
          for (int k = 1; j + k < c; k++) {
            bool flag = false;
            for (int p = mx[str[i][j]]; p <= Mx[str[i][j]]; p++) {
              if (str[p][j + k] != '?') {
                flag = true;
                break;
              }
            }
            if (flag)
              break;
            for (int p = mx[str[i][j]]; p <= Mx[str[i][j]]; p++) {
              str[p][j + k] = str[i][j];
            }
          }
        }
      }
    }
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (mx.count(str[i][j])) {
          mx[str[i][j]] = std::min(mx[str[i][j]], i);
        } else {
          mx[str[i][j]] = i;
        }
        if (Mx.count(str[i][j])) {
          Mx[str[i][j]] = std::max(Mx[str[i][j]], i);
        } else {
          Mx[str[i][j]] = i;
        }
        if (my.count(str[i][j])) {
          my[str[i][j]] = std::min(my[str[i][j]], j);
        } else {
          my[str[i][j]] = j;
        }
        if (My.count(str[i][j])) {
          My[str[i][j]] = std::min(My[str[i][j]], j);
        } else {
          My[str[i][j]] = j;
        }
      }
    }

    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (str[i][j] != '?') {
          for (int k = -1; j + k >= 0; k--) {
            bool flag = false;
            for (int p = mx[str[i][j]]; p <= Mx[str[i][j]]; p++) {
              if (str[p][j + k] != '?') {
                flag = true;
                break;
              }
            }
            if (flag)
              break;
            for (int p = mx[str[i][j]]; p <= Mx[str[i][j]]; p++) {
              str[p][j + k] = str[i][j];
            }
          }
        }
      }
    }

    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (mx.count(str[i][j])) {
          mx[str[i][j]] = std::min(mx[str[i][j]], i);
        } else {
          mx[str[i][j]] = i;
        }
        if (Mx.count(str[i][j])) {
          Mx[str[i][j]] = std::max(Mx[str[i][j]], i);
        } else {
          Mx[str[i][j]] = i;
        }
        if (my.count(str[i][j])) {
          my[str[i][j]] = std::min(my[str[i][j]], j);
        } else {
          my[str[i][j]] = j;
        }
        if (My.count(str[i][j])) {
          My[str[i][j]] = std::min(My[str[i][j]], j);
        } else {
          My[str[i][j]] = j;
        }
      }
    }

    T++;
    printf("Case #%d:\n", T);
    for (int i = 0; i < r; i++) {
      printf("%s\n", str[i]);
    }
  }
}
