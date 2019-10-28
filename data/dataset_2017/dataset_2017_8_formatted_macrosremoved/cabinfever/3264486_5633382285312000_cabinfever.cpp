#include <bits/stdc++.h>

using namespace std;

long long n, a[20], ans;
int T;

int main() {
  freopen("bl.in", "r", stdin);
  freopen("bl.out", "w", stdout);
  cin >> T;
  a[0] = 1;
  for (int i = 1; i <= 18; i++)
    a[i] = a[i - 1] * 10 + 1;
  for (int ii = 1; ii <= T; ii++) {
    cin >> n;
    printf("Case #%d: ", ii);
    ans = n;
    int cnt = 0;
    for (int i = 18; i >= 0; i--) {
      while (n >= a[i] && cnt < 9)
        n -= a[i], cnt++;
    }
    cout << ans - n << endl;
  }
  return 0;
}
