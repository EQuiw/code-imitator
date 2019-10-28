
/*
Contest: Google Code Jam 2017 [Qualification Round]
Problem: A. Oversized Pancake Flipper (15 Points)

Author: Phawin Prongpaophan
*/

#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;

int n, k;
char board[2222];
int dp[2222];

int solve() {
  scanf("%s", board);
  scanf("%d", &k);
  n = strlen(board);
  // Reset Phase
  int flipCount = 0;
  int cumulativeFlip = 0;
  for (int i = 0; i <= n; i++)
    dp[i] = 0;
  // Flip Phase!
  for (int i = 0; i + k - 1 < n; i++) {
    int curState = 0;
    if (board[i] == '-')
      curState = 1;
    cumulativeFlip += dp[i];
    curState += cumulativeFlip;
    curState %= 2;
    if (curState == 0)
      continue; // No Flip
    flipCount++;
    cumulativeFlip++;
    dp[i + k] -= 1;
  }
  // Check Phase!
  for (int i = n - k + 1; i < n; i++) {
    int curState = 0;
    if (board[i] == '-')
      curState = 1;
    cumulativeFlip += dp[i];
    curState += cumulativeFlip;
    curState %= 2;
    if (curState == 0)
      continue; // Good
    return -1;  // Impossible!
  }
  return flipCount;
}

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("SmallOutput.txt", "w", stdout);
  int tc;
  scanf("%d", &tc);
  for (int p = 1; p <= tc; p++) {
    printf("Case #%d: ", p);
    int ans = solve();
    if (ans < 0) {
      printf("IMPOSSIBLE\n");
      continue;
    }
    printf("%d\n", ans);
  }
  return 0;
}
