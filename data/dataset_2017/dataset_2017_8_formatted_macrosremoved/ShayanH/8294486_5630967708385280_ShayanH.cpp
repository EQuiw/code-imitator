#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

const int MAXN = 1 * 1000 + 10;

pii h[MAXN];

int main() {
  ios::sync_with_stdio(false);

  int tt;
  cin >> tt;
  for (int tc = 1; tc <= tt; tc++) {
    cout << "Case #" << tc << ": ";
    int d, n;
    cin >> d >> n;
    for (int i = 0; i < n; i++)
      cin >> h[i].second >> h[i].first;
    sort(h, h + n);

    double max_t = 0;
    for (int i = 0; i < n; i++) {
      int vi = h[i].first, ki = h[i].second;
      double nxt = d;
      double t = 0;
      for (int j = 0; j < i; j++) {
        int vj = h[j].first, kj = h[j].second;
        if (kj > ki) {
          double cx = (double)(vj * ki - vi * kj) / (double)(vj - vi);
          if (cx < nxt && cx > kj) {
            t += (double)(nxt - cx) / (double)vj;
            nxt = cx;
          }
        }
      }
      if (ki < nxt)
        t += (double)(nxt - ki) / (double)vi;

      max_t = max(max_t, t);
    }

    cout << fixed << setprecision(6) << (double)d / max_t << endl;
  }
  return 0;
}
