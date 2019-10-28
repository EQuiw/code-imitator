#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;
typedef long long int ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
const ld pi = acos(-1);
const int MOD = 1e9 + 9;
ll solvemax(ll b, ll e, ll k) {
  ll mid = (b + e) / 2ll;
  if (k == 0)
    return LINF;
  if (k == 1)
    return max(e - mid - 1, mid - b - 1);
  k--;
  return min(solvemax(b, mid, k / 2), solvemax(mid, e, (k + 1) / 2ll));
}

ll solvemin(ll b, ll e, ll k) {
  ll mid = (b + e) / 2;
  if (k == 0)
    return LINF;
  if (k == 1)
    return min(e - mid - 1, mid - b - 1);
  k--;
  return min(solvemin(b, mid, k / 2), solvemin(mid, e, (k + 1) / 2ll));
}

void solve() {
  ll n, k;
  cin >> n >> k;
  cout << solvemax(0, n + 1, k) << " " << solvemin(0, n + 1, k) << endl;
}
int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }
  return 0;
}
