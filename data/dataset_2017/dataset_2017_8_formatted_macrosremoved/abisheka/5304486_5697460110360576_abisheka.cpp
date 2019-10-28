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
typedef vector<vector<ll>> mat;

bool cmp(pair<int, int> a, pair<int, int> b) {
  if (a.second != b.second)
    return a.second < b.second;
  return a.first < b.first;
}

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
    int n, p;
    cin >> n >> p;
    map<int, int> m[55];
    long double lo = 0.9, hi = 1.1;
    int r[55];
    for (int i = 0; i <= n - 1; i++)
      cin >> r[i];
    vector<pair<int, int>> v[55];
    for (int i = 0; i <= n - 1; i++) {
      for (int j = 0; j <= p - 1; j++) {
        int x;
        cin >> x;
        long double y = x;
        y /= r[i];
        long double ri = y / lo, le = y / hi;
        // ol(y);on;
        long double eps = 1e-9;
        int lli = -1, rri = -1;
        for (int ii = max(1, (int)le); ii <= ceil(ri); ii++) {
          long double l = lo * ii, h = hi * ii;
          if (y + eps >= l && y - eps <= h) {
            rri = ii;
            if (lli == -1)
              lli = ii;
          }
        }
        // ol(i);os;o2(lli,rri);on;
        if (lli != -1)
          v[i].push_back(make_pair(lli, rri));
      }
    }
    for (int i = 0; i <= n - 1; i++)
      sort(v[i].begin(), v[i].end(), cmp);
    int ans = 0;
    int ptr[55] = {0};
    for (int ii = 1; ii <= 1000004; ii++) {
      for (int i = 0; i <= n - 1; i++) {
        while (1) {
          if (ptr[i] == v[i].size())
            break;
          if (v[i][ptr[i]].second < ii)
            ptr[i]++;
          else
            break;
        }
      }

      while (1) {
        int cool = 0;
        for (int i = 0; i <= n - 1; i++) {
          if (ptr[i] == v[i].size())
            break;
          if (v[i][ptr[i]].first <= ii && v[i][ptr[i]].second >= ii)
            cool++;
          else
            break;
        }
        if (cool != n)
          break;
        else {
          ans++;
          for (int i = 0; i <= n - 1; i++)
            ptr[i]++;
        }
      }
    }

    cout << ans;
    cout << "\n";
  }
  return 0;
}
