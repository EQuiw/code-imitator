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
#include <string>
#include <unordered_map>
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
typedef map<int, int> mii;
typedef unordered_map<int, int> umii;

int T, N, P, r[55], tot, p[55][55], a[55];

int main() {
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    scanf("%d %d", &N, &P);
    for (int i = 0; i < N; i++) {
      scanf("%d", &r[i]);
      a[i] = 0;
    }

    // ith ingredient, jth package
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < P; j++) {
        scanf("%d", &p[i][j]);
      }
      sort(p[i], p[i] + P);
    }

    tot = 0;

    for (int i = 1; i <= 1e6; i++) {
      // Increase pointers if < 90% of required
      for (int j = 0; j < N; j++) {
        while (a[j] < P && p[j][a[j]] < r[j] * i * 0.9) {
          a[j]++;
        }
      }

      bool make = 1;

      while (make) {
        // Check if a package can be made
        for (int j = 0; j < N; j++) {
          if (a[j] >= P || p[j][a[j]] > r[j] * i * 1.1) {
            make = 0;
          }
        }

        if (make) {
          for (int j = 0; j < N; j++) {
            a[j]++;
          }
          tot++;
        }
      }
    }

    printf("Case #%d: %d\n", t, tot);
  }
}
