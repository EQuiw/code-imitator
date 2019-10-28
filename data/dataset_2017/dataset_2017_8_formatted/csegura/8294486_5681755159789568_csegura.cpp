#include <algorithm>
#include <float.h>
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <vector>

using namespace std;

int N;
double distances[100][100];
long long E[100];
double S[100];

bool dp[100][100];
double solution[100][100];

double solve(int initial, int dest) {
  if (initial == dest) {
    return 0;
  }
  if (dp[initial][dest]) {
    return solution[initial][dest];
  }
  long long life = E[initial];
  double bestCost = DBL_MAX;
  double cost = 0;
  for (int i = initial + 1; i <= dest; i++) {
    life -= distances[i - 1][i];
    if (life < 0) {
      break;
    }
    cost += distances[i - 1][i] / S[initial];
    double total = cost + solve(i, dest);
    bestCost = min(bestCost, total);
  }
  dp[initial][dest] = true;
  solution[initial][dest] = bestCost;
  return solution[initial][dest];
}

int main() {
  int tests;
  cin >> tests;
  for (int t = 0; t < tests; t++) {
    cout << "Case #" << (t + 1) << ": ";
    long long Q;
    cin >> N >> Q;
    for (int i = 0; i < N; i++) {
      cin >> E[i] >> S[i];
    }
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cin >> distances[i][j];
      }
    }
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        dp[i][j] = false;
      }
    }
    for (int i = 0; i < Q; i++) {
      int initial, dest;
      cin >> initial >> dest;
      initial--;
      dest--;
      cout << setprecision(10) << fixed << solve(initial, dest) << " ";
    }
    cout << endl;
  }
}
