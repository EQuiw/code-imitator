#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1010;

const long double eps = 1e-10;

pair<long double, long double> vec[N];

int main() {
  ios::sync_with_stdio(false);

  int T;
  cin >> T;
  cout << setprecision(12) << fixed;
  for (int t = 1; t <= T; t++) {
    long double d;
    int n;
    cin >> d >> n;

    for (int i = 0; i < n; i++) {
      cin >> vec[i].first >> vec[i].second;
    }

    sort(vec, vec + n);

    long double lo = eps, hi = 1e18;
    while (lo + eps < hi) {
      long double t = (lo + hi) / 2;

      long double P = 1e18;
      for (int i = 0; i < n; i++) {
        long double x = vec[i].first + vec[i].second * t;
        for (int j = i + 1; j < n; j++) {
          x = min(x, t * vec[j].second + vec[j].first);
        }
        P = min(P, x);
      }

      if (P < d)
        lo = t + eps;
      else
        hi = t;
    }

    // cout << "lo: " << lo << endl;

    long double P = 1e18;
    for (int i = 0; i < n; i++) {
      long double x = vec[i].first + vec[i].second * t;
      for (int j = i + 1; j < n; j++) {
        x = min(x, t * vec[j].second + vec[j].first);
      }
      P = min(P, x);
    }

    // cout << "P: " << P << endl;

    cout << "Case #" << t << ": " << d / lo << endl;
  }
  return 0;
}
