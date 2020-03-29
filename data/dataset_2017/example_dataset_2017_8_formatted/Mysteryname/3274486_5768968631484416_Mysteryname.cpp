
/*
Contest: Google Code Jam 2017 [Round 1C]
*/

#include <algorithm>
#include <stdio.h>
#define LL long long
#include <utility>
#include <vector>
#define P pair<LL, LL>
#define x first
#define y second
#define mp make_pair
using namespace std;

const double PI = 3.141592653589793238462643383279502884;

int n, k;

P pancake[1010];

bool pancakeCompare(const P &ls, const P &rs) { return ls.x > rs.x; }

bool largerFirst(const LL &ls, const LL &rs) { return ls > rs; }

LL getMe(int baseId) {
  int possible = n - baseId;
  if (possible < k)
    return -1;
  LL ret = (pancake[baseId].x) * (pancake[baseId].x);
  ret += (pancake[baseId].x) * (pancake[baseId].y) * 2;
  int selectLeft = k - 1;
  if (selectLeft <= 0)
    return ret;
  vector<LL> bank;
  for (int i = baseId + 1; i < n; i++) {
    LL thisOne = pancake[i].x * pancake[i].y;
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
    scanf("%lld%lld", &pancake[i].x, &pancake[i].y);
  }
  sort(pancake, pancake + n, pancakeCompare);
  LL best = 0;
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
