#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> Matrix;

const int INF = 1e9 + 7;
const double PI = acos(-1);
const double EPS = 1e-9;

const int N = 1e2 + 5;

ii cities[N];
double dist[N][N];

int main() {
  int t, n, e, s, d, u, v, q;
  cin >> t;

  for (int caseNr = (1); caseNr < (t + 1); ++caseNr) {
    cout << "Case #" << caseNr << ":";
    cin >> n >> q;
    for (int i = (0); i < (n); ++i) {
      cin >> cities[i].first >> cities[i].second;
    }
    for (int i = (0); i < (n); ++i) {
      for (int j = (0); j < (n); ++j) {
        cin >> dist[i][j];
        if (dist[i][j] < 0)
          dist[i][j] = 1e18;
      }
    }
    for (int i = (0); i < (n); ++i)
      dist[i][i] = 0;
    for (int k = (0); k < (n); ++k)
      for (int i = (0); i < (n); ++i)
        for (int j = (0); j < (n); ++j)
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    double time[N] = {0};
    for (int i = (1); i < (N); ++i)
      time[i] = 1e18;
    for (int u = (0); u < (n); ++u) {
      for (int v = (u + 1); v < (n); ++v) {
        if (dist[u][v] <= cities[u].first) {
          time[v] = min(time[v], time[u] + dist[u][v] / cities[u].second);
        }
      }
    }
    for (int i = (0); i < (q); ++i) {
      cin >> u >> v;
      printf(" %.8f", time[v - 1]);
    }
    printf("\n");
  }
  return 0;
}
