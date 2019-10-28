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
  freopen("/Users/user/Downloads/B-small-attempt0.in", "r", stdin);
  freopen("key.out", "w", stdout);
  cin >> T;
  for (int q = 1; q <= T; q++) {
    ll n;
    cin >> n;
    vector<int> v;
    while (n > 0) {
      v.push_back(n % 10);
      n /= 10;
    }
    reverse((v).begin(), (v).end());
    int bg = 0, sm = 0;
    for (int i = 1; i < ((int)(v).size()); i++)
      if (v[i] > v[i - 1])
        bg = i;
      else if (v[i] < v[i - 1]) {
        sm = i;
        break;
      }
    if (sm != 0) {
      v[bg]--;
      for (int i = bg + 1; i < ((int)(v).size()); i++)
        v[i] = 9;
    }
    ll res = 0;
    for (int i = 0; i < ((int)(v).size()); i++)
      res = res * 10 + v[i];
    printf("Case #%d: %lld\n", q, res);
  }
  return 0;
}
