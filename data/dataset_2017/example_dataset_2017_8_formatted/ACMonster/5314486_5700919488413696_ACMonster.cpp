// Problem A

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int get() {
  char c;
  while (c = getchar(), c != '-' && (c < '0' || c > '9'))
    ;
  bool flag = (c == '-');
  if (flag)
    c = getchar();
  int x = 0;
  while (c >= '0' && c <= '9') {
    x = x * 10 + c - '0';
    c = getchar();
  }
  return flag ? -x : x;
}

bool flag[5][4][101][101][101];
int dp[5][4][101][101][101];

int solve(int m, int cur, int x, int y, int z) {
  if (!x && !y && !z)
    return 0;
  if (flag[m][cur][x][y][z])
    return dp[m][cur][x][y][z];
  flag[m][cur][x][y][z] = true;
  int ans = 0;
  int b[4] = {0, x, y, z};
  for (int i = 1; i <= 3; i++)
    if (b[i]) {
      b[i]--;
      int tmp = solve(m, (cur + i) % m, b[1], b[2], b[3]);
      if (!cur)
        tmp++;
      ans = max(ans, tmp);
      b[i]++;
    }
  return dp[m][cur][x][y][z] = ans;
}

int main() {
  int totalTest = get();
  for (int test = 1; test <= totalTest; test++) {
    int n = get(), m = get();
    int a[4];
    memset(a, 0, sizeof(a));
    for (int i = 0; i < n; i++)
      a[get() % m]++;
    int ans = a[0] + solve(m, 0, a[1], a[2], a[3]);
    printf("Case #%d: %d\n", test, ans);
  }
  return 0;
}
