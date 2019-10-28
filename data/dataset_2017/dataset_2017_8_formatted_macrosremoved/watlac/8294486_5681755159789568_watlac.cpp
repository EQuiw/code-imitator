#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 100;

int e[N], s[N], d[N][N];
ld dp[N];

int main() {

  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d: ", qq);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
      cin >> e[i] >> s[i];
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        cin >> d[i][j];
    int u, v;
    cin >> u >> v;
    dp[n - 1] = 0;
    for (int i = n - 2; i >= 0; i--) {
      dp[i] = -1;
      ll sum = 0;
      for (int j = i + 1; j < n; j++) {
        sum += d[j - 1][j];
        if (sum <= e[i] && dp[j] >= -0.5) {
          ld add = sum * 1.0 / s[i];
          if (dp[i] == -1.0 || dp[j] + add < dp[i])
            dp[i] = dp[j] + add;
        }
      }
    }
    printf("%.10f\n", (double)dp[0]);
  }

  return 0;
}
