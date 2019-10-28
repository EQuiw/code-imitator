#include <algorithm>
#include <bitset>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
typedef long double ld;
typedef vector<vector<ll>> mat;

int main() {
  ios_base::sync_with_stdio(false);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int t, t1 = 0;
  cin >> t;
  while (t--) {
    t1++;
    cout << "Case #";
    cout << t1;
    cout << ": ";
    int n;
    ld d;
    cin >> d >> n;
    pair<long double, long double> p[1005];
    for (int i = 0; i <= n - 1; i++)
      cin >> p[i].first >> p[i].second;
    sort(p, p + n);
    long double time[1005];
    time[n - 1] = (d - p[n - 1].first) / p[n - 1].second;

    for (int i = n - 2; i >= 0; i--) {
      time[i] = max(time[i + 1], (d - p[i].first) / p[i].second);
    }
    ld ans = d / time[0];
    cout << fixed << setprecision(10) << ans << "\n";
  }
  return 0;
}
