#include <iostream>
#include <map>
#include <math.h>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
using namespace std;

char board[30][30];

int main() {
  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    int c, i, j, r;
    scanf("%d %d", &r, &c);
    for (i = 0; i < r; i++)
      scanf("%s", board[i]);
    for (i = 0; i < r; i++)
      for (j = 1; j < c; j++)
        if (board[i][j] == '?')
          board[i][j] = board[i][j - 1];
    for (i = 0; i < r; i++)
      for (j = c - 2; j >= 0; j--)
        if (board[i][j] == '?')
          board[i][j] = board[i][j + 1];
    for (i = 1; i < r; i++)
      if (board[i][0] == '?')
        for (j = 0; j < c; j++)
          board[i][j] = board[i - 1][j];
    for (i = r - 2; i >= 0; i--)
      if (board[i][0] == '?')
        for (j = 0; j < c; j++)
          board[i][j] = board[i + 1][j];

    printf("Case #%d:\n", t);
    for (i = 0; i < r; i++)
      printf("%s\n", board[i]);
  }
}
