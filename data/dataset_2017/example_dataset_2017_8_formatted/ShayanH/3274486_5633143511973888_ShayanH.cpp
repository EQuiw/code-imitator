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

int n;
double u;
double p[MAXN];

bool check(double x) {
  double tot = 0;
  for (int i = 0; i < n; i++)
    if (p[i] < x)
      tot += x - p[i];
  return (tot <= u ? true : false);
}

int main() {
  ios::sync_with_stdio(false);
  int tt;
  cin >> tt;
  for (int tc = 1; tc <= tt; tc++) {
    cout << "case #" << tc << ": ";

    int k;
    cin >> n >> k;
    cin >> u;
    for (int i = 0; i < n; i++)
      cin >> p[i];

    double l = 0, r = 1.0;
    for (int j = 0; j < 100; j++) {
      double mid = (l + r) / 2;
      if (check(mid))
        l = mid;
      else
        r = mid;
    }

    double ans = 1.0;
    for (int i = 0; i < n; i++)
      ans = ans * max(p[i], l);
    cout << fixed << setprecision(6) << ans << endl;
  }
  return 0;
}
