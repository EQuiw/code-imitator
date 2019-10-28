#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <cassert>
#include <unordered_map>
#endif
#include <cmath>
#include <ctime>
#include <iomanip>
#include <queue>
#include <sstream>
#include <stack>
//#include "utils/haha.h"
using namespace std;
typedef pair<int, int> PII;
typedef pair<string, string> PSS;
typedef pair<int, PII> PIP;
typedef long long ll;
typedef pair<ll, ll> PLL;
#define CLS(x, v) (memset((x), (v), sizeof((x))))

int n, q;
int dis[128][128];
void solve(int ncase) {
  cout << "Case #" << ncase << ": ";
  cin >> n >> q;
  vector<int> total(n);
  vector<int> speed(n);
  for (int i = 0; i < n; i++) {
    cin >> total[i] >> speed[i];
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> dis[i][j];
    }
  }
  int h1, h2;
  cin >> h1 >> h2;
  vector<double> dp(n, -1);
  dp[0] = 0;
  for (int i = 0; i < n; i++) {
    // i horse
    ll sum = 0;
    for (int j = i + 1; j < n; j++) {
      sum += dis[j - 1][j];
      if (sum > total[i])
        break;
      double tmp = dp[i] + (sum * 1.0 / speed[i]);
      if (dp[j] < 0 || dp[j] > tmp)
        dp[j] = tmp;
    }
  }
  cout << dp[n - 1] << endl;
}

int main() {
  // ios::sync_with_stdio(false);
  cout << std::fixed;
  cout << setprecision(16);
#ifdef _zzz_
  // freopen("in.txt", "r", stdin);
  // freopen("out.txt", "w", stdout);
#endif
  int T = 1;
  scanf("%d", &T);
  // cin >> T;
  int ncase = 0;
  while (T--) {
    solve(++ncase);
  }
}
