#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long LL;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
void open() {
  freopen("D:/OneDrive/Code/GCJ/B-small-attempt0 (3).in", "r", stdin);
  freopen("D:/OneDrive/Code/GCJ/out.txt", "w", stdout);
}

int ac[1500];
int aj[1500];
int memo[1500][730][2][2];

int dp(int minute, int left, int cur, int st_with) {
  if (minute == 1440) {
    if (left != 0)
      return 10000;
    if (cur == st_with)
      return 0;
    return 1;
  }

  if (memo[minute][left][cur][st_with] != -1)
    return memo[minute][left][cur][st_with];

  int ans = 10000;

  if (cur == 0) {
    if (ac[minute]) {
      ans = dp(minute + 1, left, 1, st_with) + 1;
    } else {
      if (left > 0) {
        ans = dp(minute + 1, left - 1, 0, st_with);
      }
      if (!aj[minute]) {
        ans = min(ans, dp(minute + 1, left, 1, st_with) + 1);
      }
    }
  } else {
    if (aj[minute]) {
      if (left > 0) {
        ans = dp(minute + 1, left - 1, 0, st_with) + 1;
      }
    } else {
      ans = dp(minute + 1, left, 1, st_with);
      if (!ac[minute] && left > 0) {
        ans = min(ans, dp(minute + 1, left - 1, 0, st_with) + 1);
      }
    }
  }

  return memo[minute][left][cur][st_with] = ans;
}

int main(void) {
  open();
  int tc;
  scanf("%d", &tc);

  for (int ct = 1; ct <= tc; ct++) {
    int c, j;
    scanf("%d", &c);
    scanf("%d", &j);

    memset(ac, false, sizeof(ac));
    memset(aj, false, sizeof(aj));
    memset(memo, -1, sizeof(memo));

    for (int i = 0; i < c; i++) {
      int st, en;
      scanf("%d", &st);
      scanf("%d", &en);
      for (int j = st; j < en; j++)
        ac[j] = true;
    }

    for (int i = 0; i < j; i++) {
      int st, en;
      scanf("%d", &st);
      scanf("%d", &en);
      for (int j = st; j < en; j++)
        aj[j] = true;
    }
    int ans = 1000000000;
    if (!ac[0]) {
      ans = min(ans, dp(1, 719, 0, 0));
    }

    if (!aj[0]) {
      ans = min(ans, dp(1, 720, 1, 1));
    }

    printf("Case #%d: %d\n", ct, ans);

    cerr << "Test " << ct << " done \n";
  }
  return 0;
}
