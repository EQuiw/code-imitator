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
#ifdef HOME
  freopen("A.in", "rt", stdin);
  freopen("A.out", "wt", stdout);
  clock_t start = clock();
#endif
  solution();
#ifdef HOME
  cerr << "Total time: " << fixed << setprecision(3)
       << double(clock() - start) / double(CLOCKS_PER_SEC) << endl;
#endif
  return EXIT_SUCCESS;
}

typedef long long ll;
#define int ll

#define N 1024
int n, d;
struct horse {
  int x, s;
} h[N];

bool operator<(const horse &a, const horse &b) {
  if (a.x != b.x)
    return a.x < b.x;
  return a.s > b.s;
}

void solve() {
  sort(h, h + n);
  double t_max = 0.0;
  for (int i = 0; i < n; ++i) {
    double t = double(d - h[i].x) / double(h[i].s);
    t_max = max(t_max, t);
  }
  cout << fixed << double(d) / t_max;
}

void solution() {
  int T;
  cin >> T;
  cout.precision(9);
  for (int t = 0; t < T; ++t) {
    cerr << t + 1 << endl;
    cout << "Case #" << t + 1 << ": ";
    cin >> d >> n;
    for (int i = 0; i < n; ++i)
      cin >> h[i].x >> h[i].s;
    solve();
    cout << '\n';
  }
}
