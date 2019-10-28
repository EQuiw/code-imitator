#include <algorithm>
#include <bits/stdc++.h>
#include <queue>
#include <stdio.h>
#include <vector>
using std::vector;
struct BipartiteMatching {
  vector<int> L;
  vector<int> R;
  vector<vector<int>> G;
  vector<int> dist;
  BipartiteMatching(int n, int m) {
    L.resize(n, -1);
    R.resize(m, -1);
    G.resize(n);
    dist.resize(n);
  }
  void add_edge(int from, int to) { G[from].push_back(to); }
  bool bfs() {
    std::queue<int> que;
    for (int i = 0; i < L.size(); i++) {
      if (L[i] == -1) {
        dist[i] = 0;
        que.push(i);
      } else {
        dist[i] = -1;
      }
    }
    bool flag = false;
    while (!que.empty()) {
      int idx = que.front();
      que.pop();
      for (int to : G[idx]) {
        if (R[to] == -1)
          flag = true;
        else if (dist[R[to]] == -1) {
          dist[R[to]] = dist[idx] + 1;
          que.push(R[to]);
        }
      }
    }
    return flag;
  }
  bool dfs(int idx) {
    for (int to : G[idx]) {
      if (R[to] == -1 || (dist[idx] < dist[R[to]] && dfs(R[to]))) {
        R[to] = idx;
        L[idx] = to;
        return true;
      }
    }
    dist[idx] = -1;
    return false;
  }
  int matching() {
    int ret = 0;
    while (bfs()) {
      for (int i = 0; i < L.size(); i++) {
        if (L[i] == -1 && dfs(i)) {
          ret++;
        }
      }
    }
    return ret;
  }
};
int arr[60];
long long pack[60][60];
int idx[60];
long long m10(int i) { return i - (i / 10); }
long long M10(int i) { return i + (i / 10); }
bool matrix[10][10];
int main() {
  int tc;
  scanf("%d", &tc);
  int T = 0;
  while (tc--) {
    int n, p;
    scanf("%d%d", &n, &p);
    for (int i = 0; i < n; i++) {
      scanf("%d", &arr[i]);
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < p; j++) {
        scanf("%lld", &pack[i][j]);
      }
    }
    for (int i = 0; i < p; i++) {
      for (int j = 0; j < p; j++) {
        matrix[i][j] = false;
      }
    }
    if (n == 2) {
      BipartiteMatching bm(p, p);
      for (int c = 1; c <= 1000000; c++) {
        for (int i = 0; i < p; i++) {
          for (int j = 0; j < p; j++) {
            if (m10(arr[0] * c) <= pack[0][i] &&
                pack[0][i] <= M10(arr[0] * c) &&
                m10(arr[1] * c) <= pack[1][j] &&
                pack[1][j] <= M10(arr[1] * c)) {
              matrix[i][j] = true;
            }
          }
        }
      }
      for (int i = 0; i < p; i++) {
        for (int j = 0; j < p; j++) {
          if (matrix[i][j]) {
            bm.add_edge(i, j);
          }
        }
      }

      T++;
      printf("Case #%d: %d\n", T, bm.matching());
    } else if (n == 1) {
      std::set<int> set;
      for (int c = 1; c <= 1000000; c++) {
        for (int i = 0; i < p; i++) {
          if (m10(arr[0] * c) <= pack[0][i] && pack[0][i] <= M10(arr[0] * c)) {
            set.insert(i);
          }
        }
      }
      T++;
      printf("Case #%d: %d\n", T, set.size());
    } else {
      T++;
      printf("Case #%d: %d\n", T, 0);
      assert(false);
    }
  }
}
