
#include <algorithm>
#include <assert.h>
#include <bitset>
#include <climits>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef std::pair<int, int> pii;
template <typename T>
using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template <typename T>
using max_heap = std::priority_queue<T, std::vector<T>, std::less<T>>;
using namespace std;

int w[50 + 2][50][50 + 2][50];
int rW[50 + 2][50][50 + 2][50];
pii parent[50 + 2][50];
int n, p;
int r[50];
int q[50 + 2][50];
pii interval[50 + 2][50];
bool visited[50 + 2][50];

bool intersect(pii i1, pii i2) {
  if (i1.second < i2.first || i1.first > i2.second)
    return false;
  return true;
}

bool bfs(pii s, pii t) {
  for (int i = (0); i < (n + 2); i++) {
    for (int j = (0); j < (p); j++) {
      visited[i][j] = false;
    }
  }
  queue<pii> q;
  q.push(s);
  visited[s.first][s.second] = true;
  parent[s.first][s.second] = {-1, -1};
  while (!q.empty()) {
    pii u = q.front();
    q.pop();
    for (int i = (0); i < (n + 2); i++) {
      for (int j = (0); j < (p); j++) {
        if (!visited[i][j] && rW[u.first][u.second][i][j] > 0) {
          q.push({i, j});
          parent[i][j] = u;
          visited[i][j] = true;
        }
      }
    }
  }
  return (visited[t.first][t.second] == true);
}

int ford(pii s, pii t) {
  pii u, v;
  for (int i = (0); i < (n + 2); i++) {
    for (int j = (0); j < (p); j++) {
      for (int ii = (0); ii < (n + 2); ii++) {
        for (int jj = (0); jj < (p); jj++) {
          rW[i][j][ii][jj] = w[i][j][ii][jj];
        }
      }
    }
  }

  int max_flow = 0;
  while (bfs(s, t)) {
    int path_flow = INT_MAX;
    for (v = t; v != s; v = parent[v.first][v.second]) {
      u = parent[v.first][v.second];
      path_flow = ((path_flow) < (rW[u.first][u.second][v.first][v.second])
                       ? (path_flow)
                       : (rW[u.first][u.second][v.first][v.second]));
    }

    for (v = t; v != s; v = parent[v.first][v.second]) {
      u = parent[v.first][v.second];
      rW[u.first][u.second][v.first][v.second] -= path_flow;
      rW[v.first][v.second][u.first][u.second] += path_flow;
    }

    max_flow += path_flow;
  }

  return max_flow;
}

void reset() {
  for (int i = (0); i < (n + 2); i++) {
    for (int j = (0); j < (p); j++) {
      for (int ii = (0); ii < (n + 2); ii++) {
        for (int jj = (0); jj < (p); jj++) {
          w[i][j][ii][jj] = 0;
          rW[i][j][ii][jj] = 0;
        }
      }
    }
  }

  for (int i = (0); i < (n + 2); i++) {
    for (int j = (0); j < (p); j++) {
      parent[i][j] = {-1, -1};
    }
  }
}

bool isValid(pii interval) { return interval.first <= interval.second; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int NUMBER_OF_TESTS;
  cin >> NUMBER_OF_TESTS;
  for (int t = 1; t <= NUMBER_OF_TESTS; t++) {
    cin >> n >> p;
    reset();
    for (int i = (1); i < (n + 1); i++) {
      cin >> r[i];
    }
    for (int i = (1); i < (n + 1); i++) {
      for (int j = (0); j < (p); j++) {
        cin >> q[i][j];
        interval[i][j] = {(int)ceil(q[i][j] / (1.1 * r[i])),
                          (int)floor(q[i][j] / (0.9 * r[i]))};
      }
    }
    for (int j = (0); j < (p); j++) {
      if (isValid(interval[1][j]))
        w[0][0][1][j] = 1;
      if (isValid(interval[n][j]))
        w[n][j][n + 1][0] = 1;
    }
    for (int i = (0); i < (n); i++) {
      for (int j = (0); j < (p); j++) {
        for (int k = (0); k < (p); k++) {
          if (intersect(interval[i][j], interval[i + 1][k]) &&
              isValid(interval[i][j]) && isValid(interval[i + 1][k])) {
            w[i][j][i + 1][k] = 1;
          }
        }
      }
    }
    cout << "Case #" << t << ": " << ford({0, 0}, {n + 1, 0}) << "\n";
  }
  return 0;
}
