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
int uni[6];

int pickMax(int curColor) {
  int ans = 0;
  if (ans == curColor)
    ans = 1;
  for (int i = 0; i < 6; i++) {
    if (i == curColor)
      continue;
    if (uni[ans] < uni[i])
      ans = i;
  }
  return ans;
}
void solve() {
  int n;
  cin >> n;
  string stuff = "ROYGBV";
  for (int i = 0; i < 6; i++)
    cin >> uni[i];
  int ans[1000];
  for (int i = 0; i < n; i++)
    ans[i] = -1;
  int init = pickMax(-1);
  uni[init]--;
  ans[0] = init;
  // cout<<init<<endl;
  int left = 1;
  int right = n - 1;
  bool onLeft = true;
  while (true) {
    int ind;
    if (onLeft) {
      ind = left;
      left++;
    } else {
      ind = right;
      right--;
    }
    if (ans[ind] != -1)
      break;

    int prev;
    if (ind == n - 1)
      prev = ans[0];
    else if (!onLeft)
      prev = ans[ind + 1];
    else
      prev = ans[ind - 1];
    int val = pickMax(prev);

    uni[val]--;
    ans[ind] = val;
    onLeft = !onLeft;
  }

  bool bad = false;
  for (int i = 0; i < 6; i++) {
    if (uni[i] < 0) {
      bad = true;
    }
  }
  // for(int i=0; i< n; i++) cout<<stuff[ans[i]];
  for (int i = 1; i < n; i++) {
    if (ans[i] == ans[i - 1])
      bad = true;
  }
  if (ans[0] == ans[n - 1])
    bad = true;
  if (bad) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }
  for (int i = 0; i < n; i++)
    cout << stuff[ans[i]];
  cout << endl;
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
