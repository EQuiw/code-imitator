#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
using namespace std;

long long n, k;

map<long long, long long> f;

void work() {
  scanf("%lld%lld", &n, &k);
  priority_queue<long long> q;
  while (!q.empty())
    q.pop();
  f.clear();
  q.push(n);
  f[n] = 1;
  while (!q.empty()) {
    long long x = q.top();
    // printf("x=%lld ", x);
    q.pop();
    long long y = f[x];
    // printf("y = %lld k = %lld\n", y, k);
    if (y >= k) {
      printf("%lld %lld\n", x / 2, (x - 1) / 2);
      return;
    }
    k -= y;
    if (f[x / 2] == 0) {
      q.push(x / 2);
      // printf("push %lld\n", x/2);
    }
    f[x / 2] += y;
    if (f[(x - 1) / 2] == 0) {
      q.push((x - 1) / 2);
      // printf("push %lld\n", (x-1)/2);
    }
    f[(x - 1) / 2] += y;
  }
}

int main() {
  int TC;
  freopen("C-small-1-attempt0.in", "r", stdin);
  freopen("C-small-1-attempt0.out", "w", stdout);
  scanf("%d", &TC);
  for (int tc = 1; tc <= TC; ++tc) {
    printf("Case #%d: ", tc);
    work();
  }
}