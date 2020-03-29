
/*
Contest: Google Code Jam 2017 [Round 2]
*/

#include <algorithm>
#include <stdio.h>
using namespace std;

int n, p;
int bank[5];

int easyCase() {
  int ret = bank[0];
  ret += (bank[1] / 2);
  ret += (bank[1] % 2);
  return ret;
}

int dp3[111][111];
int dp3s[111][111];

void dynamicPreparation() {
  for (int i = 0; i <= 100; i++)
    for (int j = 0; j <= 100; j++)
      dp3[i][j] = 0;
  for (int i = 0; i <= 100; i++)
    for (int j = 0; j <= 100; j++) {
      if (i - 3 >= 0)
        dp3[i][j] = max(dp3[i][j], dp3[i - 3][j - 0] + 1);
      if (j - 3 >= 0)
        dp3[i][j] = max(dp3[i][j], dp3[i - 0][j - 3] + 1);
      if (i > 0 && j > 0)
        dp3[i][j] = max(dp3[i][j], dp3[i - 1][j - 1] + 1);

      dp3s[i][j] = dp3[i][j];

      if (i > 0)
        dp3s[i][j] = max(dp3s[i][j], dp3[i - 1][j] + 1);
      if (j > 0)
        dp3s[i][j] = max(dp3s[i][j], dp3[i][j - 1] + 1);
    }
}

int solve() {
  scanf("%d%d", &n, &p);
  for (int i = 0; i < p; i++)
    bank[i] = 0;
  for (int i = 0; i < n; i++) {
    int tmp;
    scanf("%d", &tmp);
    bank[tmp % p]++;
  }
  // Get Answer
  if (p == 2)
    return easyCase();
  return dp3s[bank[1]][bank[2]] + bank[0];
}

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-Small.txt", "w", stdout);
  dynamicPreparation();
  int tc;
  scanf("%d", &tc);
  for (int t = 1; t <= tc; t++) {
    printf("Case #%d: ", t);
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}
