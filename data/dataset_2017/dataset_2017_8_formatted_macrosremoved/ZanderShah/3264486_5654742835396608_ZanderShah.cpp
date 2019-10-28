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

int T, N, K, first[1005], c, f, ii, l, r, second[1005];

int left(int i) {
  while (first[i] == 0) {
    i--;
  }
  return i;
}

int right(int i) {
  while (first[i] == 0) {
    i++;
  }
  return i;
}

int main() {
  scanf("%d", &T);
  for (int rr = 1; rr <= T; rr++) {

    scanf("%d %d", &N, &K);
    memset(first, 0, sizeof first);
    first[0] = first[N + 1] = -1;

    for (int i = 1; i <= K; i++) {
      c = -1;
      f = -1;
      ii = -1;

      for (int j = 1; j <= N; j++) {
        if (first[j]) {
          continue;
        }
        l = j - left(j - 1) - 1;
        r = right(j + 1) - j - 1;
        if (c < min(l, r) || (c == min(l, r) && f < max(l, r))) {
          c = min(l, r);
          f = max(l, r);
          ii = j;
        }
      }

      first[ii] = i;
      second[i] = ii;
    }

    cout << "Case #" << rr << ": " << f << " " << c << endl;
  }
}
