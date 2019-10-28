#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 110;

ll d[N][N];
long double t[N][N];

bool reaches[N][N];

ll E[N], S[N];

int main() {
  ios::sync_with_stdio(false);
  cout << fixed << setprecision(12);

  int T;
  cin >> T;
  for (int caso = 1; caso <= T; caso++) {
    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n; i++) {
      cin >> E[i] >> S[i];
    }

    memset(d, 0x3f, sizeof d);
    memset(t, 0, sizeof t);
    memset(reaches, 0, sizeof reaches);

    ll inf = d[0][0];

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        int x;
        cin >> x;
        if (x != -1) {
          d[i][j] = x;
        } else if (i == j) {
          d[i][j] = 0;
        }
      }
    }

    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        }
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        ll dist = d[i][j];
        if (dist != inf && dist <= E[i]) {
          t[i][j] = dist;
          t[i][j] /= S[i];
          reaches[i][j] = true;
        }
      }
    }

    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (reaches[i][k] && reaches[k][j]) {
            if (reaches[i][j])
              t[i][j] = min(t[i][j], t[i][k] + t[k][j]);
            else
              t[i][j] = t[i][k] + t[k][j];
            reaches[i][j] = true;
          }
        }
      }
    }

    cout << "Case #" << caso << ": ";

    for (int i = 0; i < q; i++) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      cout << t[u][v] << " ";
    }
    cout << "\n";
  }
  return 0;
}
