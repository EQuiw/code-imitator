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

int T, D, N;
pii horse[1005];
double t0, t1;

int main() {
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    scanf("%d %d", &D, &N);
    for (int i = 0; i < N; i++) {
      scanf("%d %d", &horse[i].first, &horse[i].second);
    }
    sort(horse, horse + N);

    t0 = 0;
    for (int i = N - 1; i >= 0; i--) {
      t1 = (D - horse[i].first) * 1.0 / horse[i].second;
      t0 = max(t0, t1);
    }

    printf("Case #%d: %.7lf\n", t, D / t0);
  }
}
