#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    int N, M;
    cin >> N >> M;
    char G[30][30];
    vector<int> cnt(N, 0);
    for (int i = 0; i < N; i++) {
      int fill = 0;
      char last;
      for (int j = 0; j < M; j++) {
        cin >> G[i][j];
        if (G[i][j] != '?') {
          cnt[i]++;
          for (int k = j - 1; k >= fill; k--)
            G[i][k] = G[i][j];
          fill = j + 1;
          last = G[i][j];
        }
      }
      for (int j = fill; j < M; j++)
        G[i][j] = last;
    }

    for (int i = 0; i < N; i++) {
      if (cnt[i] == 0) {
        int fix = 0;
        for (int j = i - 1; j >= 0 && !fix; j--)
          if (cnt[j]) {
            for (int k = 0; k < M; k++)
              G[i][k] = G[j][k];
            fix = 1;
          }
        for (int j = i + 1; j < N && !fix; j++)
          if (cnt[j]) {
            for (int k = 0; k < M; k++)
              G[i][k] = G[j][k];
            fix = 1;
          }
      }
    }

    cout << "Case #" << t << ":" << endl;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++)
        cout << G[i][j];
      cout << endl;
    }
  }
}
