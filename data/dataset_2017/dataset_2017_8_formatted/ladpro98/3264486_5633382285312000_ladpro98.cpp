#include <bits/stdc++.h>

using namespace std;

long long solve(long long n, int n_digit) {
  long long res = 0;
  for (int i = n_digit; i >= 1; --i) {
    bool found = false;
    for (int x = 9; x >= 1; --x) {
      long long cur = res;
      for (int it = 1; it <= i; ++it) {
        cur = cur * 10 + x;
      }
      if (cur <= n) {
        res = res * 10 + x;
        found = true;
        break;
      }
    }
  }
  return res;
}

bool ok(long long ans, long long n) {
  if (ans > n)
    return false;
  int last = 9;
  while (ans > 0) {
    if (last < ans % 10)
      return false;
    last = ans % 10;
    ans /= 10;
  }
  return true;
}

int main() {
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; ++tc) {
    long long n;
    cin >> n;
    long long ans = solve(n, 18);
    assert(ok(ans, n));
    cout << "Case #" << tc << ": " << ans << endl;
  }
  return 0;
}