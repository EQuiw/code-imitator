#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef pair<lli, lli> pii;

struct AugPath {
  int A, B;              // size of left, right groups
  vector<vector<int>> G; // size A
  vector<bool> visited;  // size A
  vector<int> P;         // size B

  AugPath(int _A, int _B) : A(_A), B(_B), G(_A), P(_B, -1) {}

  void AddEdge(int a, int b) { // a from left, b from right
    G[a].push_back(b);
  }
  bool Aug(int x) {
    if (visited[x])
      return 0;
    visited[x] = 1;
    /* Greedy heuristic */
    for (auto it : G[x]) {
      if (P[it] == -1) {
        P[it] = x;
        return 1;
      }
    }
    for (auto it : G[x]) {
      if (Aug(P[it])) {
        P[it] = x;
        return 1;
      }
    }
    return 0;
  }
  int MCBM() {
    int matchings = 0;
    for (int i = 0; i < A; ++i) {
      visited.resize(A, 0);
      matchings += Aug(i);
      visited.clear();
    }
    return matchings;
  }
  vector<pair<int, int>> GetMatchings() {
    vector<pair<int, int>> matchings;
    for (int i = 0; i < B; ++i) {
      if (P[i] != -1)
        matchings.emplace_back(P[i], i);
    }
    return matchings;
  }
};

int tc;

int main() {
  cin >> tc;
  for (int t = 1; t <= tc; t++) {
    int n, m;
    cin >> n >> m;
    char grid[109][109];
    char newgrid[109][109];
    char ptx[109][109];
    char ptt[109][109];
    for (int i = 0; i < 109; i++)
      for (int j = 0; j < 109; j++) {
        grid[i][j] = '.';
        newgrid[i][j] = '.';
        ptx[i][j] = 1;
        ptt[i][j] = 1;
      }
    char c;
    int x, y;
    for (int i = 0; i < m; i++) {
      cin >> c >> x >> y;
      grid[x][y] = c;
      newgrid[x][y] = c;
      if (c == 'x' || c == 'o') {
        for (int i = 1; i <= n; i++) {
          ptx[x][i] = 0;
          ptx[i][y] = 0;
        }
      }
      if (c == '+' || c == 'o') {
        for (int i = 0; (x + i) <= n && (y + i) <= n; i++) {
          ptt[x + i][y + i] = 0;
        }
        for (int i = 0; (x - i) >= 1 && (y - i) >= 1; i++) {
          ptt[x - i][y - i] = 0;
        }
        for (int i = 0; (x + i) <= n && (y - i) >= 1; i++) {
          ptt[x + i][y - i] = 0;
        }
        for (int i = 0; (x - i) >= 1 && (y + i) <= n; i++) {
          ptt[x - i][y + i] = 0;
        }
      }
    }
    AugPath mcbm(n * 3, n * 3);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        // cout << grid[i][j] << " ";
      }
      // cout << endl;
    }
    // cout << endl;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        // cout << int(ptx[i][j]) << " ";
        if (ptx[i][j] == 1) {
          mcbm.AddEdge(i - 1, j - 1);
        }
      }
      // cout << endl;
    }
    // cout << endl;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        // cout << int(ptt[i][j]) << " ";
        if (ptt[i][j] == 1) {
          mcbm.AddEdge(n + i + j - 1, n * 2 + i - j);
        }
      }
      // cout << endl;
    }
    // cout << endl;
    mcbm.MCBM();
    auto v = mcbm.GetMatchings();
    for (auto i : v) {
      if (i.first < n && i.second < n) {
        // place x at [i.first][i.second]
        if (newgrid[i.first + 1][i.second + 1] == '.') {
          newgrid[i.first + 1][i.second + 1] = 'x';
        } else {
          newgrid[i.first + 1][i.second + 1] = 'o';
        }
      } else {
        i.first = i.first - n + 1;
        i.second = i.second - n * 2;
        int firstcord = (i.first + i.second) / 2;
        int secondcord = (i.first - i.second) / 2;
        if (newgrid[firstcord][secondcord] == '.') {
          newgrid[firstcord][secondcord] = '+';
        } else {
          newgrid[firstcord][secondcord] = 'o';
        }
      }
    }
    int score = 0, added = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (newgrid[i][j] != '.') {
          if (newgrid[i][j] == 'o') {
            score += 2;
          } else {
            score++;
          }
          if (newgrid[i][j] != grid[i][j]) {
            added++;
          }
        }
        // cout << newgrid[i][j] << " ";
      }
      // cout << endl;
    }
    // cout << endl;
    printf("Case #%d: %d %d\n", t, score, added);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (newgrid[i][j] != '.') {
          if (newgrid[i][j] != grid[i][j]) {
            cout << newgrid[i][j] << " " << i << " " << j << endl;
          }
        }
        // cout << newgrid[i][j] << " ";
      }
      // cout << endl;
    }
    // cout << endl;
  }
}