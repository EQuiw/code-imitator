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
long long ans;
long long pows[20];
void solve(long long n, int digLeft, int prevDig, long long cur) {
  if (cur * pows[digLeft] > n)
    return;
  if (ans != 0)
    return;
  if (digLeft == 0) {
    ans = cur;
    return;
  }
  for (int i = 9; i >= prevDig; i--) {
    solve(n, digLeft - 1, i, cur * 10 + i);
  }
}
int main() {
  ios::sync_with_stdio(false);
  freopen("test.txt", "r", stdin);
  freopen("test1.txt", "w", stdout);
  // freopen(".out","w",stdout);
  int t;
  cin >> t;
  pows[0] = 1;
  for (int i = 0; i < 19; i++) {
    pows[i + 1] = pows[i] * 10;
  }
  for (int i = 1; i <= t; i++) {
    ans = 0;
    long long n;
    cin >> n;
    int digs = log10(n) + 1;
    solve(n, digs, 0, 0);
    cout << "Case #" << i << ": " << ans << endl;
  }
}
