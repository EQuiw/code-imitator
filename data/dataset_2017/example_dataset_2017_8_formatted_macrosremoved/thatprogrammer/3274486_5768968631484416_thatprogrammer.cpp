// Hi
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;
struct cake {
  long long r, h;
};
bool comp(cake a, cake b) {
  if (a.r == b.r)
    return a.h < b.h;
  return a.r < b.r;
}
void solve() {
  int n, k;
  cake cs[1000];
  cin >> n >> k;
  for (int i = 0; i < n; i++)
    cin >> cs[i].r >> cs[i].h;
  sort(cs, cs + n, comp);
  // for(int i=0; i< n; i++) cout<<cs[i].r<<cs[i].h;
  long long maxH[1000][1000]; //[curcake][numLeft]
  for (int i = 0; i < n; i++)
    maxH[i][0] = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 1; j <= k; j++) {
      long long curMax = 0;
      for (int b = 0; b < i; b++) {
        curMax = max(curMax, maxH[b][j - 1]);
      }
      maxH[i][j] = curMax + 2 * cs[i].r * cs[i].h;
    }
  }
  long double ans = 0;
  long double pi = 3.14159265358979323846;
  for (int i = 0; i < n; i++) {
    // cout<<maxH[i][k]<<" ";
    long double cur = cs[i].r * cs[i].r + maxH[i][k];
    cur *= pi;
    ans = max(ans, cur);
  }
  cout << fixed << setprecision(10) << ans << endl;
}
int main() {
  ios::sync_with_stdio(false);
  freopen("test.txt", "r", stdin);
  freopen("test1.txt", "w", stdout);
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }
}
