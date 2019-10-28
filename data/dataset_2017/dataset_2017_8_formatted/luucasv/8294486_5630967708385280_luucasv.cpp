#include <bits/stdc++.h>
#define fr(a, b, c) for (int a = b, __ = c; a < __; ++a)
#define dbg(x) cerr << ">>>> " << x << endl;
#define _ << " , " <<
#define S second
#define K first

using namespace std;

typedef pair<int, int> ii;
ii h[11111];

int n, d;

bool can(long double s) {
  bool ok = 1;
  fr(i, 0, n) {
    if (s < h[i].S || (fabs(s - h[i].S) < 1e-8))
      continue;
    long double rel = s - h[i].S, t = h[i].K / rel, nd = t * s;
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
    fr(i, 0, n) {
      cin >> h[i].K >> h[i].S;
      if (cas == 37)
        dbg(h[i].K _ h[i].S)
    }
    long double lo = 1e-6, hi = 1e40;
    fr(inter, 0, 5000) {
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