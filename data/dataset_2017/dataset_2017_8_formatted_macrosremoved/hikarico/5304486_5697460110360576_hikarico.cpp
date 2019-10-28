#include <bits/stdc++.h>
using namespace std;
const int N = 55;

int t, n, m, start[N];
int a[N], M[N][N];
vector<pair<int, int>> v[N];

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
      v[i].clear();
    }
    set<int> p;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        scanf("%d", &M[i][j]);
        double lb = M[i][j] / (0.9 * a[i]);
        double ub = M[i][j] / (1.1 * a[i]);
        // lbi <= index <= ubi
        int lbi = (int)floor(lb);
        int ubi = (int)ceil(ub);
        if (ubi <= lbi) {
          v[i].push_back({ubi, lbi});
          p.insert(ubi);
          p.insert(lbi);
        }
      }
      sort(v[i].begin(), v[i].end());
      // for (auto& c : v[i]) {
      // cout << " " << c.first << ":" << c.second;
      // }
      // cout << endl;
      start[i] = 0;
    }
    int kits = 0;
    for (auto &x : p) {
      bool pass = true;
      while (pass) {
        // cout << x << endl;
        for (int i = 0; i < n; ++i) {
          bool ok = false;
          while (start[i] < v[i].size() && v[i][start[i]].second < x)
            ++start[i];
          if (start[i] < v[i].size() && v[i][start[i]].first <= x &&
              x <= v[i][start[i]].second) {
            ok = true;
          } else {
            pass = false;
            break;
          }
        }
        // for (int i = 0; i < n; ++i)
        // cout << start[i] << ' ';
        // cout << endl;
        if (pass) {
          // cout << "PASS " << x << endl;
          ++kits;
          for (int i = 0; i < n; ++i)
            ++start[i];
        }
      }
    }
    static int tc = 0;
    printf("Case #%d: %d\n", ++tc, kits);
  }
}
