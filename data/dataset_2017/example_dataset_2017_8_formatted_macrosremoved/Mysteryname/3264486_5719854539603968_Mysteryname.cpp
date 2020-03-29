
/*
Contest: Google Code Jam 2017 [Qualification Round]
Problem: D. Fashion Show
Note: This Solution is for SMALL INPUT only

Author: Phawin Prongpaophan
*/
#include <algorithm>
#include <queue>
#include <stdio.h>
using namespace std;

int n, m;

bool plusSolver[1111][1111];
bool multSolver[1111][1111];
char board[1111][1111];

bool rowGone[1111];
bool columnGone[1111];

struct modify {
  char type;
  int r, c;
};
queue<modify> togo;

void solve() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      plusSolver[i][j] = false;
      multSolver[i][j] = false;
      board[i][j] = '.';
    }
  for (int i = 0; i < m; i++) {
    char wst[50];
    scanf("%s", wst);
    char det = wst[0];
    int r, c;
    scanf("%d%d", &r, &c);
    // printf("Detect: (%c) [%d][%d]\n",det,r,c);
    r--;
    c--;
    if (det == '+' || det == 'o')
      plusSolver[r][c] = true;
    if (det == 'x' || det == 'o')
      multSolver[r][c] = true;
    board[r][c] = det;
  }
  // Part A: Plus Solver
  if (n == 1) {
    plusSolver[0][0] = true;
  } else // General Case
  {
    for (int i = 0; i < n; i++)
      plusSolver[0][i] = true;
    for (int i = 1; i + 1 < n; i++)
      plusSolver[n - 1][i] = true;
  }
  // Part B: Multiplication Solver
  for (int i = 0; i < n; i++)
    rowGone[i] = false;
  for (int j = 0; j < n; j++)
    columnGone[j] = false;
  // Check for Current Run
  for (int j = 0; j < n; j++) {
    if (!multSolver[0][j])
      continue;
    rowGone[0] = true;
    columnGone[j] = true;
  } // There can be at most ONE multiplication
  // Solve Time!
  for (int i = 0; i < n; i++) {
    if (rowGone[i])
      continue;
    for (int j = 0; j < n; j++) {
      if (columnGone[j])
        continue;
      // Place!
      multSolver[i][j] = true;
      rowGone[i] = true;
      columnGone[j] = true;
      break;
    }
  }
  // Now we have solution!
  int score = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      if (plusSolver[i][j])
        score++;
      if (multSolver[i][j])
        score++;
      char mod = '.';
      if (plusSolver[i][j] && multSolver[i][j])
        mod = 'o';
      else if (plusSolver[i][j])
        mod = '+';
      else if (multSolver[i][j])
        mod = 'x';
      // Check
      if (mod != board[i][j]) {
        modify tst;
        tst.type = mod;
        tst.r = i;
        tst.c = j;
        togo.push(tst);
      }
    }
  // Print Answer
  printf("%d %d\n", score, togo.size());
  while (!togo.empty()) {
    modify w = togo.front();
    togo.pop();
    printf("%c %d %d\n", w.type, w.r + 1, w.c + 1);
  }
}

int main() {
  freopen("D-small-attempt0.in", "r", stdin);
  freopen("D-SmallOutput.txt", "w", stdout);
  int tc;
  scanf("%d", &tc);
  for (int p = 1; p <= tc; p++) {
    printf("Case #%d: ", p);
    solve();
  }
  return 0;
}
