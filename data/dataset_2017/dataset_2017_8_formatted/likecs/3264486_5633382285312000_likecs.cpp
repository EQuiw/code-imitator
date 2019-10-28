/******************************************
 *    AUTHOR:         BHUVNESH JAIN        *
 *    INSTITUITION:   BITS PILANI, PILANI  *
 ******************************************/
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef long double LD;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;

const int MAX = 1e5 + 5;

bool solve(int n) {
  vector<int> dig;
  while (n) {
    dig.push_back(n % 10);
    n /= 10;
  }
  reverse(dig.begin(), dig.end());
  for (int i = 1; i < dig.size(); ++i) {
    if (dig[i] < dig[i - 1]) {
      return false;
    }
  }
  return true;
}

vector<int> v;

int main() {
  ios_base::sync_with_stdio(false);
  for (int i = 1; i < MAX; ++i) {
    if (solve(i)) {
      v.push_back(i);
    }
  }
  int t, n, ans;
  cin >> t;
  for (int T = 1; T <= t; ++T) {
    cout << "Case #" << T << ": ";

    cin >> n;
    ans = -1;
    for (int x : v) {
      if (x <= n) {
        ans = x;
      } else {
        break;
      }
    }
    cout << ans << "\n";
  }
  return 0;
}