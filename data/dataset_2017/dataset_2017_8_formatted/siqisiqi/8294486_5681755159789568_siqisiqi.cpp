#include <cstdio>
#include <iostream>
#define time TTime
using namespace std;

const int N = 101;
long long dist[N][N], D[N][N];
int E[N], speed[N];
int n, q;

double time[N];
int vis[N];

int main() {

  int T;
  cin >> T;
  for (int test = 0; test < T; ++test) {
    cin >> n >> q;
    for (int i = 0; i < n; ++i)
      cin >> E[i] >> speed[i];
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j) {
        cin >> dist[i][j];
        if (dist[i][j] == -1)
          dist[i][j] = 1000000000000; // 1e12
        D[i][j] = dist[i][j];
      }
    for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
          if (D[i][j] > D[i][k] + D[k][j])
            D[i][j] = D[i][k] + D[k][j];

    cout << "Case #" << 1 + test << ":";
    for (int ii = 0; ii < q; ++ii) {
      int s, t;
      cin >> s >> t;
      --s, --t;

      for (int j = 0; j < n; ++j) {
        time[j] = 1e13;
        vis[j] = 0;
      }
      time[s] = 0;

      for (int i = 0; i < n; ++i) {

        int mini = -1;
        for (int j = 0; j < n; ++j)
          if (vis[j] == 0)
            if (mini == -1 || time[mini] > time[j])
              mini = j;
        vis[mini] = 1;

        for (int j = 0; j < n; ++j) {
          if (vis[j] == 0)
            if (D[mini][j] <= E[mini])
              if (time[j] > time[mini] + 1.0 * D[mini][j] / speed[mini])
                time[j] = time[mini] + 1.0 * D[mini][j] / speed[mini];
        }
      }
      printf(" %.6f", time[t]);
    }
    printf("\n");
  }

  return 0;
}
