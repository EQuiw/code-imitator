#include <bits/stdc++.h>

using namespace std;

#define SMALL
//#define LARGE

int t;
long long x, ans;

void dfs(const long long& k, const long long& x, const long long& now, const int& b) {
  if (k == 0) {
    ans = ans > now ? ans : now;
    return;
  }
  if (ans / 10 >= now * k + k)
    return;
  if (b)
    dfs(k / 10, x - x / k * k, 10 * now + 9, b);
  else {
    int d = x / k;
    for (int i = 0; i <= d; ++i)
      if (i >= now % 10)
        dfs(k / 10, x - x / k * k, 10 * now + i, i < d);
  }
}

int main()
{
#ifdef SMALL
  freopen("B-small.in", "r", stdin);
  freopen("B-small.out", "w", stdout);
#endif
#ifdef LARGE
  freopen("B-large.in", "r", stdin);
  freopen("B-large.out", "w", stdout);
#endif
  scanf("%d", &t);
  for (int Case = 1; Case <= t; ++Case) {
    scanf("%lld", &x);
    long long k = 1;
    while (k <= x / 10)
      k *= 10;
    ans = 0;
    dfs(k, x, 0, 0);
    printf("Case #%d: %lld\n", Case, ans);
  }
  return 0;
}