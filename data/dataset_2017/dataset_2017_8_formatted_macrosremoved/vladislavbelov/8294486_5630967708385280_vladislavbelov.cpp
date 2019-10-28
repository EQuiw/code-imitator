/*
 * Author: Vladislav Belov
 */
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

void solution();

int main() {
  ios::sync_with_stdio(false);

  solution();

  return EXIT_SUCCESS;
}

typedef long long ll;

ll n, d;
struct horse {
  ll x, s;
} h[1024];

bool operator<(const horse &a, const horse &b) {
  if (a.x != b.x)
    return a.x < b.x;
  return a.s > b.s;
}

void solve() {
  sort(h, h + n);
  double t_max = 0.0;
  for (ll i = 0; i < n; ++i) {
    double t = double(d - h[i].x) / double(h[i].s);
    t_max = max(t_max, t);
  }
  cout << fixed << double(d) / t_max;
}

void solution() {
  ll T;
  cin >> T;
  cout.precision(9);
  for (ll t = 0; t < T; ++t) {
    cerr << t + 1 << endl;
    cout << "Case #" << t + 1 << ": ";
    cin >> d >> n;
    for (ll i = 0; i < n; ++i)
      cin >> h[i].x >> h[i].s;
    solve();
    cout << '\n';
  }
}
