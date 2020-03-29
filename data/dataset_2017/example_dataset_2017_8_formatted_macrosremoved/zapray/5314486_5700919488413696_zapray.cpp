
#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;

using namespace std;

int cnt[4];
int n, p;

int dp[105][105][105];
int solve(int x, int y, int z) {
  if (dp[x][y][z] != -1)
    return dp[x][y][z];

  int ans = -1;
  if (x) {
    int left = ((x - 1) + y * 2 + z * 3) % p;
    ans = max(ans, solve(x - 1, y, z) + (left == 0));
  }
  if (y) {
    int left = (x + (y - 1) * 2 + z * 3) % p;
    ans = max(ans, solve(x, y - 1, z) + (left == 0));
  }
  if (z) {
    int left = (x + y * 2 + (z - 1) * 3) % p;
    ans = max(ans, solve(x, y, z - 1) + (left == 0));
  }
  return dp[x][y][z] = ans;
}

int main() {
  int csn;
  cin >> csn;
  for (int cs = 1; cs <= csn; cs++) {
    printf("Case #%d: ", cs);

    cin >> n >> p;
    memset(cnt, 0, sizeof(cnt));
    memset(dp, -1, sizeof(dp));
    dp[0][0][0] = 0;
    int ans = 0;
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      cnt[x % p]++;
    }
    ans = cnt[0] + solve(cnt[1], cnt[2], cnt[3]);
    printf("%d\n", ans);
  }

  return 0;
}
