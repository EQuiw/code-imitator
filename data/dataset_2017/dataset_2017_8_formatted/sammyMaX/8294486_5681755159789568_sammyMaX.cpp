#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ifstream fin("C-small-attempt1.in");
ofstream fout("C-small1.out");

const int SZ = 105;
// [i][j] is cost to go from i to j
int n, q;
ll cost[SZ];
ll hspeed[SZ], hrange[SZ];

void solve() {
  fin >> n >> q;
  for (int i = 0; i < n; i++)
    fin >> hrange[i] >> hspeed[i];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      int tmp;
      fin >> tmp;
      if (j == i + 1)
        cost[i] = tmp;
    }
  for (int i = 0; i < q; i++) {
    int a, b;
    fin >> a >> b;
  }
  double dp[SZ] = {}, dprange[SZ] = {};
  dprange[0] = hrange[0];
  for (int i = 1; i < n; i++) {
    double mindp = 1e15;
    for (int j = 0; j < i; j++) {
      if (dprange[j] >= cost[i - 1])
        dp[j] += 1.0 * cost[i - 1] / hspeed[j], dprange[j] -= cost[i - 1];
      else
        dp[j] = 1e15, dprange[j] = 0;
      mindp = min(mindp, dp[j]);
    }
    dp[i] = mindp, dprange[i] = hrange[i];
  }
  fout << dp[n - 1] << '\n';
  cout << dp[n - 1] << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  fout << fixed << setprecision(12);

  int t;
  fin >> t;
  for (int i = 0; i < t; i++)
    fout << "Case #" << i + 1 << ": ", solve();
}
