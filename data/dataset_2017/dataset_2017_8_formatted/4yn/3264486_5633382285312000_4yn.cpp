#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int tc;

lli ctdy(string input) {
  lli dp[18][2][10];
  memset(dp, 0, sizeof(dp));
  for (int i = '0'; i <= input[0]; i++) {
    if (i != input[0]) {
      dp[0][0][i - '0'] = 1;
    } else {
      dp[0][1][i - '0'] = 1;
    }
  };
  for (int i = 0; i < input.size() - 1; i++) {
    for (int j = 0; j <= 9; j++) {
      for (int k = j; k <= 9; k++) {
        dp[i + 1][0][k] += dp[i][0][j];
      }
    }
    for (int j = 0; j <= 9; j++) {
      if (dp[i][1][j] == 0)
        continue;
      for (int k = j; k <= input[i + 1] - '0'; k++) {
        if (k != input[i + 1] - '0') {
          dp[i + 1][0][k] += dp[i][1][j];
        } else {
          dp[i + 1][1][k] += dp[i][1][j];
        }
      }
    }
  }
  lli sum = 0;
  for (int i = 0; i <= 9; i++) {
    sum += dp[input.size() - 1][0][i];
    sum += dp[input.size() - 1][1][i];
  }
  return sum;
}

int main() {
  cin >> tc;
  for (int t = 1; t <= tc; t++) {
    char c[30];
    lli num;
    string s;
    scanf("%s", c);
    sscanf(c, "%lld", &num);
    s = c;
    lli goal = ctdy(s);
    // cout << num << " ";
    // cout << goal << endl;
    lli ub = num, lb = 0, m;
    while (ub - lb > 1) {
      m = (ub + lb) / 2;
      num = m;
      sprintf(c, "%lld", num);
      s = c;
      if (ctdy(s) != goal) {
        lb = m;
      } else {
        ub = m;
      }
    }
    // cout << ub << " " << lb << endl;
    printf("Case #%d: %lld\n", t, ub);
  }
}