#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 1e3;

int main() {

  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d: ", qq);
    ld d;
    int n;
    cin >> d >> n;
    vector<pair<ld, ld>> h(n);
    for (int i = 0; i < n; i++)
      cin >> h[i].first >> h[i].second;
    sort((h).begin(), (h).end());
    for (int i = n - 2; i >= 0; i--) {
      ld p1 = h[i].first, v1 = h[i].second;
      ld p2 = h[i + 1].first, v2 = h[i + 1].second;
      if (v1 < v2)
        continue;
      ld t = (p2 - p1) / (v1 - v2);
      ld x = t * v1;
      if (p1 + x > d)
        continue;
      double v = (d - p1) / (t + (d - (p1 + x)) / v2);
      h[i].second = v;
    }
    ld ans = h[0].second * d / (d - h[0].first);
    printf("%.10lf\n", (double)ans);
  }

  return 0;
}
