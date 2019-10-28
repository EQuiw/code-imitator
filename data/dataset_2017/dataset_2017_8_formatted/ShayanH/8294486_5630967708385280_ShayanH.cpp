#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define SQR(a) ((a) * (a))
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(), (x).end()
#define CLR(x, a) memset(x, a, sizeof x)
#define VAL(x) #x << " = " << (x) << "   "
#define FOREACH(i, x)                                                          \
  for (__typeof((x).begin()) i = (x).begin(); i != (x).end(); i++)
#define FOR(i, n) for (int i = 0; i < (n); i++)
#define X first
#define Y second

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
      cin >> h[i].Y >> h[i].X;
    sort(h, h + n);

    double max_t = 0;
    for (int i = 0; i < n; i++) {
      int vi = h[i].X, ki = h[i].Y;
      double nxt = d;
      double t = 0;
      for (int j = 0; j < i; j++) {
        int vj = h[j].X, kj = h[j].Y;
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
