
/*
Contest: Google Code Jam 2017 [Round 1C]
*/

#include <algorithm>
#include <stdio.h>

#include <utility>
#include <vector>

using namespace std;

const double PI = 3.141592653589793238462643383279502884;

int n, k;

pair<long long, long long> pancake[1010];

bool pancakeCompare(const pair<long long, long long> &ls,
                    const pair<long long, long long> &rs) {
  return ls.first > rs.first;
}

bool largerFirst(const long long &ls, const long long &rs) { return ls > rs; }

long long getMe(int baseId) {
  int possible = n - baseId;
  if (possible < k)
    return -1;
  long long ret = (pancake[baseId].first) * (pancake[baseId].first);
  ret += (pancake[baseId].first) * (pancake[baseId].second) * 2;
  int selectLeft = k - 1;
  if (selectLeft <= 0)
    return ret;
  vector<long long> bank;
  for (int i = baseId + 1; i < n; i++) {
    long long thisOne = pancake[i].first * pancake[i].second;
    thisOne *= 2;
    bank.push_back(thisOne);
  }
  sort(bank.begin(), bank.end(), largerFirst);
  for (int i = 0; i < selectLeft; i++)
    ret += bank[i];
  return ret;
}

double solve() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++) {
    scanf("%lld%lld", &pancake[i].first, &pancake[i].second);
  }
  sort(pancake, pancake + n, pancakeCompare);
  long long best = 0;
  for (int i = 0; i < n; i++)
    best = max(best, getMe(i));
  double ans = PI;
  ans *= best;

  return ans;
}

int main() {
  freopen("A-small-attempt0.in", "r", stdin);
  freopen("A-Small.txt", "w", stdout);
  int tc;
  scanf("%d", &tc);
  for (int t = 1; t <= tc; t++) {
    printf("Case #%d: ", t);
    double ans = solve();
    printf("%.9f\n", ans);
  }
  return 0;
}
