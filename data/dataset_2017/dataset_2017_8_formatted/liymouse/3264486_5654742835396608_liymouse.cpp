#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

typedef long long i64d;

using namespace std;

void ins(i64d x, i64d num, vector<pair<i64d, i64d>> &b) {
  int id = -1;
  for (int i = 0; i < b.size(); i++)
    if (b[i].first == x)
      id = i;
  if (id == -1)
    b.push_back(make_pair(x, num));
  else
    b[id].second += num;
}
int main() {
  freopen("C-small-1-attempt2.in", "r", stdin);
  freopen("C-small-1-attempt2.out", "w", stdout);
  int cas;
  scanf("%d", &cas);
  for (int ca = 1; ca <= cas; ca++) {
    printf("Case #%d: ", ca);
    i64d n, k;
    scanf("%lld %lld", &n, &k);
    i64d num = 1;
    vector<pair<i64d, i64d>> a;
    a.push_back(make_pair(n, 1));
    while (k > num) {
      k -= num;
      num <<= 1;

      vector<pair<i64d, i64d>> b;
      for (int i = 0; i < a.size(); i++) {
        i64d x = (a[i].first - 1) / 2;
        ins(x, a[i].second, b);
        ins(a[i].first - 1 - x, a[i].second, b);
      }
      a = b;
    }
    if (a.size() == 2 && a[0].first < a[1].first)
      swap(a[0], a[1]);
    i64d res = (k <= a[0].second) ? a[0].first : a[1].first;
    if (res % 2 == 1)
      printf("%lld %lld\n", (res - 1) / 2, (res - 1) / 2);
    else
      printf("%lld %lld\n", (res - 1) / 2 + 1, (res - 1) / 2);
  }
  return 0;
}