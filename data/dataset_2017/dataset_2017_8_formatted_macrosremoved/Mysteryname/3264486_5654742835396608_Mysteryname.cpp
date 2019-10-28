
/*
Contest: Google Code Jam 2017 [Qualification Round]
Problem: C. Bathroom Stalls (30 Points)

Author: Phawin Prongpaophan
*/
#include <algorithm>
#include <stdio.h>
#include <utility>

using namespace std;

pair<long long, long long> solve(long long pos, long long n) {
  if (pos == 1) {
    pair<long long, long long> ret;
    ret.first = (n + 1) / 2;
    ret.second = (n + 1) - (ret.first);
    return ret;
  }
  // Go!
  long long smallHalf = (n - 1) / 2;
  long long bigHalf = (n - 1) - smallHalf;
  long long rem = pos - 1;
  if (rem % 2 == 1) // Big
  {
    return solve((rem + 1) / 2, bigHalf);
  }
  return solve(rem / 2, smallHalf);
}

int main() {
  freopen("C-small-1-attempt0.in", "r", stdin);
  freopen("C-Small1Output.txt", "w", stdout);
  int tc;
  scanf("%d", &tc);
  for (int p = 1; p <= tc; p++) {
    printf("Case #%d: ", p);
    long long n, k;
    scanf("%lld%lld", &n, &k);
    pair<long long, long long> ans = solve(k, n);
    printf("%lld %lld\n", ans.second - 1, ans.first - 1);
  }
  return 0;
}
