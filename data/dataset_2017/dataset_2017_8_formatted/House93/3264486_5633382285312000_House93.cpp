#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

#define DEBUG 0
#define N 20

typedef long long LL;

int dig[N];
int n;
LL ans;

bool dfs(int pos, int now, int small) {
  if (pos == n - 1) {
    return true;
  }
  int top = 9;
  if (small == 0) {
    if (dig[pos + 1] >= now) {
      ans = ans * 10 + dig[pos + 1];
      if (dfs(pos + 1, dig[pos + 1], 0)) {
        return true;
      }
      ans /= 10;
    }
    top = dig[pos + 1] - 1;
  }
  for (int i = top; i >= now; --i) {
    ans = ans * 10 + i;
    if (dfs(pos + 1, i, 1)) {
      return true;
    }
    ans /= 10;
  }
  return false;
}

int main() {
  if (!DEBUG) {
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
  }
  int t, T = 1;
  LL x;

  scanf("%d", &t);
  while (t--) {
    scanf("%lld", &x);
    n = 0;
    while (x) {
      dig[n++] = x % 10;
      x /= 10;
    }
    reverse(dig, dig + n);
    for (int i = dig[0]; i >= 0; --i) {
      ans = i;
      if (dfs(0, i, i != dig[0])) {
        break;
      }
    }
    printf("Case #%d: %lld\n", T++, ans);
  }
  return 0;
}