#include <bits/stdc++.h>
using namespace std;
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
