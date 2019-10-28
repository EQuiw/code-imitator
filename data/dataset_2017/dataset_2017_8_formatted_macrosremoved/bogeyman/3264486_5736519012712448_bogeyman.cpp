#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <queue>
#include <regex>
#include <set>
#include <stack>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
const int S = int(2e5) + 10;
const int INF = int(1e9) + 7;
const ll MOD = ll(1e4) + 7;
const double EPS = 1e-12;
const ll magic = ll(5e4);

int T;

int main() {
  //	freopen("key.in", "r", stdin);
  freopen("key.out", "w", stdout);
  cin >> T;
  for (int q = 1; q <= T; q++) {
    string s;
    int k, num = 0;
    cin >> s >> k;
    for (int i = ((int)(s).size()) - 1; i >= k - 1; i--)
      if (s[i] == '-') {
        for (int j = 0; j < k; j++) {
          if (s[i - j] == '+')
            s[i - j] = '-';
          else
            s[i - j] = '+';
        }
        num++;
      }
    for (int i = 0; i < k - 1; i++)
      if (s[i] == '-')
        num = -1;
    if (num < 0)
      printf("Case #%d: IMPOSSIBLE\n", q);
    else
      printf("Case #%d: %d\n", q, num);
  }
  return 0;
}
