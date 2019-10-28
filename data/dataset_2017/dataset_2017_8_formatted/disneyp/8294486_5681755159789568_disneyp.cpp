#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
int n, q;
double e[1010], s[1010];
double d[1010][1010];
double D[1010][1010];
int u[1001], v[1010];
double T[1010][1001];
double mic[1010];
bool edge[1010][1010];

double ans;

void build_easy() {
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (j == i + 1) {
        D[i][j] = d[i][j];
      } else {
        D[i][j] = D[i][j - 1] + d[j - 1][j];
      }
    }
  }

  // have D[i][j]

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      edge[i][j] = false;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (e[i] >= D[i][j]) {
        T[i][j] = D[i][j] / s[i];
        edge[i][j] = true;
      }
    }
  }

  // mic
  mic[1] = 0.0;
  for (int i = 2; i <= n; i++)
    mic[i] = -1.0;
  for (int i = 2; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      if (!edge[j][i])
        continue;
      if (mic[i] < 0.0 || mic[i] > mic[j] + T[j][i]) {
        mic[i] = mic[j] + T[j][i];
      }
    }
  }
  ans = mic[n];
}
int main() {
  freopen("C.in", "r", stdin);
  freopen("C.txt", "w", stdout);
  int tt;
  cin >> tt;
  for (int aa = 0; aa < tt; aa++) {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
      cin >> e[i] >> s[i];
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++)
        scanf("%lf", &d[i][j]);
    }
    for (int i = 0; i < q; i++) {
      cin >> u[i] >> v[i];
    }

    build_easy();

    cout << "Case #" << aa + 1 << ": ";
    printf("%.6lf\n", ans);
  }

  return 0;
}