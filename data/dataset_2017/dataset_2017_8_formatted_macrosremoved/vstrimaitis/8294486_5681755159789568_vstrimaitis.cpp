
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

ll w[100][100];
ll e[100], s[100];
int n, q;
ld best[100][100];

ld solve(int u, int v) {
  for (int i = (0); i < (n); i++)
    for (int j = (0); j < (n); j++)
      best[i][j] = (1LL << 31) - 1;
  best[n - 1][n - 1] = 0;
  for (int i = (n - 2); i >= (0); i--) {
    best[i][i] = 0;
    ll totalDist = 0;
    int prev = i;
    for (int j = (i + 1); j < (n); j++) {
      if (w[prev][j] < 0)
        continue;
      totalDist += w[prev][j];
      if (totalDist > e[i]) {
        for (int k = (j); k < (n); k++) {
          best[i][k] = best[i][prev] + best[prev][k];
        }
        break;
      }
      best[i][j] =
          ((totalDist / (ld)s[i]) < (best[i][prev] + w[prev][j] / (ld)s[prev])
               ? (totalDist / (ld)s[i])
               : (best[i][prev] + w[prev][j] / (ld)s[prev]));
      prev = j;
    }
  }
  return best[0][n - 1];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int NUMBER_OF_TESTS;
  cin >> NUMBER_OF_TESTS;
  for (int t = 1; t <= NUMBER_OF_TESTS; t++) {
    cin >> n >> q;
    for (int i = (0); i < (n); i++) {
      cin >> e[i] >> s[i];
    }
    for (int i = (0); i < (n); i++) {
      for (int j = (0); j < (n); j++) {
        int a;
        cin >> a;
        w[i][j] = a;
      }
    }
    cout << "Case #" << t << ": ";
    for (int i = (0); i < (q); i++) {
      int u, v;
      cin >> u >> v;
      cout << fixed << setprecision(12) << solve(u, v) << " ";
    }
    cout << "\n";
  }
  return 0;
}
