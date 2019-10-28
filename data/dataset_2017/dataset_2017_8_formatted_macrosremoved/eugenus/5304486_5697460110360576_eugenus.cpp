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

typedef pair<int, int> par;
typedef long long int tint;

int r[55];
int q[55][55];
par cand[55][55];

int main() {
  freopen("test.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int t;
  cin >> t;
  int n, p;

  for (int caso = (1); caso < (t + 1); caso++) {
    cin >> n >> p;
    vector<int> l;
    for (int i = 0; i < (n); i++)
      cin >> r[i];
    bool used[55][55];
    for (int i = 0; i < (n); i++)
      for (int j = 0; j < (n); j++)
        used[i][j] = false;
    for (int i = 0; i < (n); i++) {
      for (int j = 0; j < (p); j++)
        cin >> q[i][j];
    }
    for (int i = 0; i < (n); i++) {
      for (int j = 0; j < (p); j++) {
        int a = (100 * q[i][j] + 110 * r[i] - 1) / (110 * r[i]);
        a = max(a, 1);
        int b = (100 * q[i][j]) / (90 * r[i]);
        if (a <= b)
          l.push_back(a);
        par p;
        p.first = b - a;
        p.second = b;
        cand[i][j] = p;
      }
      sort(cand[i], cand[i] + p);
    }
    sort(l.begin(), l.end());
    int ans = 0;

    for (int m = 0; m < (l.size()); m++) {
      bool ok = true;
      int k = l[m];
      int ac[55];
      for (int i = 0; i < (n); i++) {
        bool oki = false;
        for (int j = 0; j < (p); j++) {
          if (!used[i][j]) {
            int a = cand[i][j].second - cand[i][j].first;
            int b = cand[i][j].second;
            if (a <= k and k <= b) {
              // used[i][j] = true;
              ac[i] = j;
              oki = true;
              break;
            }
          }
        }
        if (!oki) {
          ok = false;
          break;
        }
      }

      if (ok) {
        // cout << k << endl;
        for (int i = 0; i < (n); i++)
          used[i][ac[i]] = true;
        ans++;
      }
    }

    cout << "Case #" << caso << ": " << ans << endl;
  }

  return 0;
}
