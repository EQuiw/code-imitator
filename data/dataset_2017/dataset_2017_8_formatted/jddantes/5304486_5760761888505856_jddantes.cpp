#include <bits/stdc++.h>

using namespace std;

char grid[25][25];
int R, C;

void floodVert(int row, int col, char c) {
  for (int i = row - 1; i >= 0; i--) {
    if (grid[i][col] != '?')
      break;
    grid[i][col] = c;
  }
  for (int i = row + 1; i < R; i++) {
    if (grid[i][col] != '?')
      break;
    grid[i][col] = c;
  }
}

void floodHor(int row, int col, char c) {
  for (int j = col + 1; j < C; j++) {
    if (grid[row][j] != '?')
      break;
    grid[row][j] = c;
  }
  for (int j = col - 1; j >= 0; j--) {
    if (grid[row][j] != '?')
      break;
    grid[row][j] = c;
  }
}

int main() {
  int cases;
  scanf("%d", &cases);

  for (int e = 0; e < cases; e++) {
    scanf("%d %d", &R, &C);

    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        scanf(" %c", &grid[i][j]);
      }
    }

    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        if (grid[i][j] != '?') {
          floodVert(i, j, grid[i][j]);
        }
      }
    }

    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        if (grid[i][j] != '?') {
          floodHor(i, j, grid[i][j]);
        }
      }
    }

    printf("Case #%d:\n", e + 1);
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        printf("%c", grid[i][j]);
      }
      printf("\n");
    }
  }

  return 0;
}