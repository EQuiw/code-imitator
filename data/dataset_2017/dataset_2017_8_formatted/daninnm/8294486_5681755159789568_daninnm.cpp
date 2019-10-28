#include <cstdio>
#include <iomanip>
#include <iostream>

using namespace std;

int T;
int n, q;
long long e[128];
double s[128];
long long d[128][128];
long long dist[128];
int u, v;
double mintime[128];
double temp;
double dp[128][128]; /// dp[index][horse]
inline long long rem(int index, int horse) {
  return e[horse] - dist[index] + dist[horse];
}
int main() {
  ios_base::sync_with_stdio(false);

  freopen("in.in", "r", stdin);
  freopen("out.out", "w", stdout);
  //*/
  cin >> T;

  for (int t = 1; t <= T; ++t) {
    cin >> n >> q;
    for (int i = 0; i <= n; ++i) {
      mintime[i] = -1;
    }
    for (int i = 1; i <= n; ++i)
      cin >> e[i] >> s[i];
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j) {
        cin >> d[i][j];
        // if(d[i][j] != -1)cout << "IJ: " << i <<" " << j <<"\n";
      }
    cin >> u >> v;
    for (int i = 2; i <= n; ++i) {
      dist[i] = dist[i - 1] + d[i - 1][i];
    } // cout << d[i-1][i] << " " << i-1 << " " << i << "\n";}
    mintime[1] = 0;
    for (int i = 1; i <= n; ++i) {
      // cout << "DIST: " << dist[i] << "\n";
      for (int j = 1; j < i; ++j) {
        if (rem(i, j) >= 0) {
          temp = mintime[j] + (dist[i] - dist[j]) / s[j];
          // cout << i << " " << j << " : " << temp << "\n";
          if (mintime[i] < 0 || mintime[i] > temp)
            mintime[i] = temp;
        }
      }
    }

    cout.precision(20);
    cout << fixed;
    cout << "Case #" << t << ": " << mintime[n] << "\n";
  }

  return 0;
}
