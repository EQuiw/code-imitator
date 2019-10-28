#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void print(int testNo, vector<long double> anss) {
  cout << "Case #" << testNo << ":";
  for (long double ans : anss)
    cout << " " << ans;
  cout << endl;
}

static long double INF = 100000000000000.0L;

vector<vector<long double>> preprocess(const vector<pair<int, int>> &ESs,
                                       const vector<vector<int>> &dis) {
  int N = ESs.size();
  vector<vector<long double>> adj(N, vector<long double>(N, INF));

  for (int i = 0; i < N; ++i) {
    // adj[i][x]

    adj[i][i] = 0.0;

    priority_queue<pair<long double, int>, vector<pair<long double, int>>,
                   greater<pair<long double, int>>>
        pq;
    pq.push(make_pair(0.0, i));
    while (!pq.empty()) {
      auto cur = pq.top();
      pq.pop();
      if (adj[i][cur.second] < cur.first)
        continue;

      for (int j = 0; j < N; ++j) {
        if (cur.second == j)
          continue;
        if (dis[cur.second][j] == -1)
          continue;

        int nextNo = j;
        long double nextCost =
            cur.first +
            (static_cast<long double>(dis[cur.second][j]) / ESs[i].second);
        if (nextCost * ESs[i].second <=
            static_cast<long double>(ESs[i].first)) {
          if (nextCost < adj[i][j]) {
            adj[i][j] = nextCost;
            // cout << i << ' ' << j << ' ' << adj[i][j] << endl;
            pq.push(make_pair(nextCost, j));
          }
        }
      }
    }
  }
  return adj;
}

void floyd(vector<vector<long double>> &adj) {
  int N = adj.size();
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      if (adj[i][j] == 0.0L && i != j)
        adj[i][j] = INF;

  for (int k = 0; k < N; ++k)
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
        if (adj[i][j] > adj[i][k] + adj[k][j])
          adj[i][j] = adj[i][k] + adj[k][j];
}

int main() {
  cout << fixed;
  cout.precision(10);
  int totalTestNo;
  cin >> totalTestNo;
  for (int testNo = 1; testNo <= totalTestNo; ++testNo) {
    int N, Q;
    cin >> N >> Q;
    vector<pair<int, int>> ESs(N);
    for (int i = 0; i < N; ++i) {
      int E, S;
      cin >> E >> S;
      ESs[i] = make_pair(E, S);
    }
    vector<vector<int>> dis(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        int D;
        cin >> D;
        dis[i][j] = D;
      }
    }

    vector<pair<int, int>> UVs(Q);
    for (int i = 0; i < Q; ++i) {
      int U, V;
      cin >> U >> V;
      --U, --V;
      UVs[i] = make_pair(U, V);
    }

    vector<vector<long double>> adj = preprocess(ESs, dis);
    floyd(adj);
    vector<long double> anss(Q);
    for (int i = 0; i < Q; ++i) {
      long double ans = adj[UVs[i].first][UVs[i].second];
      anss[i] = ans;
    }

    print(testNo, anss);
  }
}
