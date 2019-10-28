#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;
typedef long double ld;

const long double inf = 1e18 + 7;

const long double eps = 1e-18;

int gcd(int a, int b) {
  while (a && b)
    a %= b, swap(a, b);
  return a + b;
}

int main() {
  ios_base::sync_with_stdio(0);

  int t;
  cin >> t;
  for (int tt = 0; tt < t; ++tt) {
    long double d;
    int n;
    cin >> d >> n;
    long double maxt = 0;
    for (int i = 0; i < n; ++i) {
      long double x, v;
      cin >> x >> v;
      maxt = max(maxt, (d - x) / v);
    }
    cout.precision(10);
    cout << "Case #" << tt + 1 << ": " << fixed << d / maxt << endl;
  }
  return 0;
}
