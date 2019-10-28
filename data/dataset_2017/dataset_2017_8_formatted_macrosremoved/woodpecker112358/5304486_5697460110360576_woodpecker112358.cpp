#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;
typedef long long mint;
typedef unsigned long long umint;
pair<int, int> q[1005][1005];
vector<int> v[1005];
int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("Bout.txt", "w", stdout);
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    int r[1005];
    int n, p;
    cin >> n >> p;
    for (int i = 0; i < (n); i++) {
      cin >> r[i];
    }

    int val;
    for (int i = 0; i < (n); i++) {
      v[i].resize(p);
      for (int j = 0; j < (p); j++) {
        cin >> v[i][j];
      }
      sort(v[i].begin(), v[i].end());
    }
    for (int i = 0; i < (n); i++) {
      for (int j = 0; j < (p); j++) {
        q[i][j].first = (v[i][j] * 10 + 11 * r[i] - 1) / (11 * r[i]);
        q[i][j].second = (v[i][j] * 10) / (9 * r[i]);
      }
    }
    int mnp[1005] = {0}, cnt = 0;
    for (int i = 0; i < (p); i++) {
      int mn = q[0][i].first, mx = q[0][i].second;
      // cout << mn <<" "<<mx<<endl;
      bool ok = true;
      if (mn > mx) {
        ok = false;
      }
      for (int j = 1; j < n && ok; j++) {
        int pos = mnp[j];
        while (pos < p && q[j][pos].second < mn) {
          pos++;
        }
        mnp[j] = pos;
        mx = min(mx, q[j][pos].second);
        mn = max(mn, q[j][pos].first);
        if (pos == p || mn > mx) {
          ok = false;
          break;
        }
        // cout << mn <<" "<<mx<<endl;
      }
      if (ok) {
        cnt++;
        for (int j = 1; j < n; j++) {
          mnp[j]++;
        }
      }
    }
    printf("Case #%d: %d\n", t, cnt);
  }
  return 0;
}
