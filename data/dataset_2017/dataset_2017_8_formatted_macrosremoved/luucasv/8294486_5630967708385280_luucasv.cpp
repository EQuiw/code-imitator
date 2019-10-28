#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
ii h[11111];

int n, d;

bool can(long double s) {
  bool ok = 1;
  for (int i = 0, __ = n; i < __; ++i) {
    if (s < h[i].second || (fabs(s - h[i].second) < 1e-8))
      continue;
    long double rel = s - h[i].second, t = h[i].first / rel, nd = t * s;
    if (nd < d)
      return 0;
  }
  return 1;
}

int main() {
  ios::sync_with_stdio(0);
  int t, cas = 1;
  cin >> t;
  while (t--) {
    cin >> d >> n;
    for (int i = 0, __ = n; i < __; ++i) {
      cin >> h[i].first >> h[i].second;
      if (cas == 37)
        cerr << ">>>> " << h[i].first << " , " << h[i].second << endl;
    }
    long double lo = 1e-6, hi = 1e40;
    for (int inter = 0, __ = 5000; inter < __; ++inter) {
      long double m = (lo + hi) / 2;
      if (can(m))
        lo = m;
      else
        hi = m;
    }
    cout << "Case #" << cas++ << ": " << setprecision(10) << fixed << hi
         << endl;
  }
}
