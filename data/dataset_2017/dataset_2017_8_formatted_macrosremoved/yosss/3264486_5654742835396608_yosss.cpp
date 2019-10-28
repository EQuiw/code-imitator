#include <bits/stdc++.h>
using namespace std;

const long long MODP = 1000000007;

void solve(void) {
  long long n, k;
  cin >> n >> k;
  long long cnt = 0;
  long long m = n;
  long long a[2] = {1, 0}, b[2];
  while (1) {
    long long newm = (m - 1) / 2;
    b[0] = b[1] = 0;
    if (m == 0) {
      cout << 0 << " " << 0;
      return;
    } else if (m == 1) {
      // m+1
      b[0] += a[1];
      b[1] += a[1];
      cnt += a[1];
      if (k <= cnt) {
        cout << newm + 1 << " " << newm;
        return;
      }
      cout << 0 << " " << 0;
      return;
    } else if (m % 2) {
      // m+1
      b[0] += a[1];
      b[1] += a[1];
      cnt += a[1];
      if (k <= cnt) {
        cout << newm + 1 << " " << newm;
        return;
      }
      // m
      b[0] += a[0] * 2;
      cnt += a[0];
      if (k <= cnt) {
        cout << newm << " " << newm;
        return;
      }
    } else {
      // m+1
      b[1] += a[1] * 2;
      cnt += a[1];
      if (k <= cnt) {
        cout << newm + 1 << " " << newm + 1;
        return;
      }
      // m
      b[0] += a[0];
      b[1] += a[0];
      cnt += a[0];
      if (k <= cnt) {
        cout << newm + 1 << " " << newm;
        return;
      }
    }
    a[0] = b[0];
    a[1] = b[1];
    m = newm;
  }
  return;
}

int main(void) {
  int T;
  cin >> T;
  for (int tcnt = 1; tcnt <= T; tcnt++) {
    cout << "Case #" << tcnt << ": ";
    solve();
    cout << endl;
  }
  return 0;
}
