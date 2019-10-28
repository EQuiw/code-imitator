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

int T, N, R, O, Y, G, B, V;
string ans;

bool best(char c) {
  bool ret = 0;

  if (R > 0 && c == 'R' && ans.back() != 'R') {
    ret |= R >= Y && R >= B;
    ret |= R >= Y && ans.back() == 'B';
    ret |= R >= B && ans.back() == 'Y';
  }

  if (B > 0 && c == 'B' && ans.back() != 'B') {
    ret |= B >= R && B >= Y;
    ret |= B >= R && ans.back() == 'Y';
    ret |= B >= Y && ans.back() == 'R';
  }

  if (Y > 0 && c == 'Y' && ans.back() != 'Y') {
    ret |= Y >= R && Y >= B;
    ret |= Y >= R && ans.back() == 'B';
    ret |= Y >= B && ans.back() == 'R';
  }

  return ret;
}

int main() {
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    scanf("%d %d %d %d %d %d %d", &N, &R, &O, &Y, &G, &B, &V);

    ans = "$";

    while (R != 0 || B != 0 || Y != 0) {
      if (best('R')) {
        ans += 'R';
        R--;
      } else if (best('B')) {
        ans += 'B';
        B--;
      } else if (best('Y')) {
        ans += 'Y';
        Y--;
      } else {
        ans = "$IMPOSSIBLE";
        break;
      }
    }

    if (ans[1] == ans.back()) {
      ans = "$IMPOSSIBLE";
    }

    printf("Case #%d: %s\n", t, ans.substr(1).c_str());
  }
}
