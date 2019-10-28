#include <algorithm>
#include <cstdio>

using namespace std;

char cake[30][30];
int r, c;
int main() {
  int T;
  scanf("%d", &T);
  for (int I = 1; I <= T; I++) {
    scanf("%d%d", &r, &c);
    for (int i = 0; i < r; i++) {
      scanf("%s", cake[i]);
    }
    bool firstempty = true;
    for (int i = 0; i < c; i++) {
      if (cake[0][i] != '?')
        firstempty = false;
    }
    if (firstempty) {
      int nonempty = 0;
      for (int i = 0; i < r; i++) {
        bool empty = true;
        for (int j = 0; j < c; j++) {
          if (cake[i][j] != '?')
            empty = false;
        }
        if (!empty) {
          nonempty = i;
          break;
        }
      }
      for (int i = 0; i < c; i++) {
        cake[0][i] = cake[nonempty][i];
      }
    }
    for (int i = 1; i < r; i++) {
      bool empty = true;
      for (int j = 0; j < c; j++) {
        if (cake[i][j] != '?')
          empty = false;
      }
      if (empty) {
        for (int j = 0; j < c; j++) {
          cake[i][j] = cake[i - 1][j];
        }
      }
    }
    for (int i = 0; i < r; i++) {
      if (cake[i][0] == '?') {
        for (int j = 0; j < c; j++) {
          if (cake[i][j] != '?') {
            cake[i][0] = cake[i][j];
            break;
          }
        }
      }
      for (int j = 0; j < c; j++) {
        if (cake[i][j] == '?') {
          cake[i][j] = cake[i][j - 1];
        }
      }
    }
    printf("Case #%d:\n", I);
    for (int i = 0; i < r; i++) {
      printf("%s\n", cake[i]);
    }
  }
}
