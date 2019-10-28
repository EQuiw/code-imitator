#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
char _;

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef pair<double, double> pdd;
typedef pair<ll, ll> pll;
typedef unordered_map<int, int> umii;

int T, N, Q, u, v, g[105][105];
ll dist[105];
pii horse[105];

// City, Horse
double dp[105][105];

double go(int c, int r, int h) {
  if (N <= c) {
    return 0;
  }

  double ret = 1L << 60;

  // Go to next town if possible
  if (g[c][c + 1] <= r) {
    ret = min(ret, go(c + 1, r - g[c][c + 1], h) +
                       g[c][c + 1] * 1.0 / horse[h].second);
  }
  // Take this horse
  if (g[c][c + 1] <= horse[c].first) {
    ret = min(ret, go(c + 1, horse[c].first - g[c][c + 1], c) +
                       g[c][c + 1] * 1.0 / horse[c].second);
  }

  return ret;
}

int main() {
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    scanf("%d %d", &N, &Q);
    for (int i = 1; i <= N; i++) {
      scanf("%d %d", &horse[i].first, &horse[i].second);
    }
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        scanf("%d", &g[i][j]);
      }
    }

    for (int i = 1; i <= Q; i++) {
      scanf("%d %d", &u, &v);
      printf("Case #%d: %lf\n", t, go(u, horse[1].first, 1));
    }
  }
}
