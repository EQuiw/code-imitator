#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

typedef long long int tint;
typedef pair<tint, tint> par;

par h[1100];

int main() {
  freopen("test.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int t, n, d;
  cin >> t;

  for (int caso = (1); caso < (t + 1); caso++) {
    cin >> d >> n;
    for (int i = 0; i < (n); i++)
      cin >> h[i].first >> h[i].second;
    sort(h, h + n);

    int next = n - 1;

    for (int i = (n - 2); i >= 0; i--) {
      // cout << h[i].x << " " << h[i].y << endl;
      if (h[i].second > h[next].second) {
        par q =
            make_pair(h[next].first - h[i].first, h[i].second - h[next].second);
        par arr = make_pair(d - h[next].first, h[next].second);
        // cout << i << " " << next << endl;
        // cout << q.x << " " << q.y << endl;
        // cout << arr.x << " " << arr.y << endl;
        if (q.first * arr.second >= q.second * arr.first) {
          next = i;
        }
      } else
        next = i;
    }
    // cout << next << endl;

    par arr = make_pair(d - h[next].first, h[next].second);
    double ans = d * arr.second / (arr.first + 0.0);
    cout.setf(ios::showpoint | ios::fixed);
    cout.precision(10);

    cout << "Case #" << caso << ": " << ans << endl;
  }

  return 0;
}
