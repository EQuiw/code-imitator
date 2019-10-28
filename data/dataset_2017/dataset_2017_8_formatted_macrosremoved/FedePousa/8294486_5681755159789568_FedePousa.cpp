

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int T;
int N, Q;
int Es[105], Ss[105];
int dist[105][105];
double memo[105][105];

double solve(int from, int to, int horse, int acum) {
  if (from == to)
    return 0.0;
  if (memo[from][horse] > -0.5)
    return memo[from][horse];
  double res = 1e100;
  if (dist[from][from + 1] <= Es[horse] - acum)
    res = min(res, ((double)(dist[from][from + 1]) / (double)(Ss[horse])) +
                       solve(from + 1, to, horse, acum + dist[from][from + 1]));
  if (dist[from][from + 1] <= Es[from])
    res = min(res, ((double)(dist[from][from + 1]) / (double)(Ss[from])) +
                       solve(from + 1, to, from, dist[from][from + 1]));
  memo[from][horse] = res;
  return res;
}

int main() {
  cin >> T;
  for (int caso = 1; caso <= T; caso++) {
    cin >> N >> Q;
    for (int i = 0; i < N; i++) {
      cin >> Es[i] >> Ss[i];
    }
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cin >> dist[i][j];
      }
    }
    cout << "Case #" << caso << ":";
    for (int i = 0; i < Q; i++) {
      int U, V;
      cin >> U >> V;
      for (int a = 0; a < 105; a++) {
        for (int b = 0; b < 105; b++) {
          memo[a][b] = -1;
        }
      }
      double res = solve(U - 1, V - 1, U - 1, 0);
      printf(" %.6lf", res);
      printf("\n");
    }
  }
  return 0;
}
