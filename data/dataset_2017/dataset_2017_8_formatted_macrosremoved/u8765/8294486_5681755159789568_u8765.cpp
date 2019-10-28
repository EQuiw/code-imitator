#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

typedef pair<int, int> PI;
typedef long long LL;

int h_dist[100];
int h_speed[100];
LL dist[100][100];
double travel_time[100][100];

int main() {
  int cases;

  cin >> cases;
  for (int caseid = 1; caseid <= cases; ++caseid) {
    cout << "Case #" << caseid << ":";
    int N, Q;
    cin >> N >> Q;
    assert(1 <= N && N <= 100);
    for (int i = 0; i < N; ++i) {
      cin >> h_dist[i] >> h_speed[i];
    }
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        cin >> dist[i][j];
      }
    }

    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        if (dist[j][i] == -1)
          continue;
        for (int k = 0; k < N; ++k) {
          if (dist[i][k] == -1)
            continue;
          LL tmp = dist[j][i] + dist[i][k];
          if (dist[j][k] == -1 || dist[j][k] > tmp) {
            dist[j][k] = tmp;
          }
        }
      }
    }

    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        // travel_time[i][j]: time to travel from i to j with horse of city i
        if (dist[i][j] == -1 || dist[i][j] > h_dist[i]) {
          travel_time[i][j] = -1;
          continue;
        }
        travel_time[i][j] = (double)dist[i][j] / h_speed[i];
      }
    }

    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        if (travel_time[j][i] == -1)
          continue;
        for (int k = 0; k < N; ++k) {
          if (travel_time[i][k] == -1)
            continue;
          double tmp = travel_time[j][i] + travel_time[i][k];
          if (travel_time[j][k] == -1 || travel_time[j][k] > tmp) {
            travel_time[j][k] = tmp;
          }
        }
      }
    }

    for (int q = 0; q < Q; ++q) {
      int from, to;
      cin >> from >> to;
      printf(" %.20f", travel_time[from - 1][to - 1]);
    }
    cout << endl;
  }
  return 0;
}
