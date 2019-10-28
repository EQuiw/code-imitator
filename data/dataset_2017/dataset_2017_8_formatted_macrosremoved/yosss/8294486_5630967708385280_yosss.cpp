#include <bits/stdc++.h>
using namespace std;

const long long MODP = 1000000007;

long long k[1024], s[1024];
void solve(void) {
  long long d, n;
  cin >> d >> n;
  double maxtime = 0.0;
  for (int i = 0; i < n; i++) {
    cin >> k[i] >> s[i];
    maxtime = max(maxtime, (d - k[i] + 0.0) / s[i]);
  }
  printf("%.8f\n", d / maxtime);
  return;
}

int main(void) {
  int T;
  cin >> T;
  for (int tcnt = 1; tcnt <= T; tcnt++) {
    cout << "Case #" << tcnt << ": ";
    solve();
  }
  return 0;
}
