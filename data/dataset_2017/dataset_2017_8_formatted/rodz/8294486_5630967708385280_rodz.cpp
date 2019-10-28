#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fi first
#define se second

using namespace std;

typedef pair<int, int> ii;
typedef long long ll;

int main() {
  int t, casecnt = 1;
  cin >> t;

  while (t--) {
    int d, n;
    cin >> d >> n;
    double mintime = 0.0;
    for (int i = 0; i < n; i++) {
      int k, s;
      cin >> k >> s;
      double time = 1.0 * (d - k) / (1.0 * s);
      mintime = max(mintime, time);
    }
    printf("Case #%d: %lf\n", casecnt++, 1.0 * d / mintime);
  }

  return 0;
}
