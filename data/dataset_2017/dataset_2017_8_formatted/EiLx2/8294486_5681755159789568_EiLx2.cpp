#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

#define LL long long
#define LD double

LL T, N, Q, c[110][110], e[110], s[110], d[110];
LD dp[110][110];

int main() {
  ifstream fin("input.in");
  ofstream fout("output.out");
  fin >> T;

  int t;
  for (t = 1; t <= T; t++) {
    fout << "Case #" << t << ": ";
    fin >> N >> Q;

    LL i, j;
    for (i = 1; i <= N; i++)
      fin >> e[i] >> s[i];

    for (i = 1; i <= N; i++)
      for (j = 1; j <= N; j++)
        fin >> c[i][j];

    fin >> i >> j;

    memset(dp, 0, sizeof(dp));
    memset(d, 0, sizeof(d));

    for (i = 2; i <= N; i++)
      d[i] = d[i - 1] + c[i - 1][i];

    for (i = N - 1; i > 0; i--)
      for (j = 1; j <= i; j++) {
        dp[i][j] = (1LL << 50);
        if (d[i + 1] - d[j] <= e[j]) {
          dp[i][j] = min(dp[i][j], 1.0 * c[i][i + 1] / s[j] +
                                       min(dp[i + 1][j], dp[i + 1][i + 1]));
        }
      }

    fout << fixed << setprecision(9) << dp[1][1] << "\n";
  }

  return 0;
}
