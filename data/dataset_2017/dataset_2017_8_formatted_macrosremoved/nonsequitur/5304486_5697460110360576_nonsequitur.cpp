#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 55;

int R[N];
int Q[N][N];

int main() {
  int T;
  scanf("%d", &T);

  // T = min(T, 10);

  for (int t = 1; t <= T; t++) {
    int n, p;
    scanf("%d %d", &n, &p);

    for (int i = 0; i < n; i++) {
      scanf("%d", R + i);
    }

    vector<tuple<int, int, int, int, int>> events;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < p; j++) {
        scanf("%d", &Q[i][j]);
        ll x = Q[i][j];
        ll r = R[i];

        ll to = (10 * x) / (9 * r);
        ll from = (10 * x) / (11 * r);
        if ((10 * x) % (11 * r))
          from++;

        from = max(from, 0ll);

        if (from <= to) {
          assert(from <= 1000000000);
          assert(to <= 1000000000);
          events.emplace_back(from, 0, to, i, j);
          events.emplace_back(to, 1, to, i, j);
        }
      }
    }

    sort(begin(events), end(events));

    set<pair<int, int>> active[N];

    int ans = 0;
    for (auto &ev : events) {
      int x, out, i, j, y;
      tie(x, out, y, i, j) = ev;

      if (out) {
        active[i].erase(make_pair(y, j));
      } else {
        active[i].insert(make_pair(y, j));

        bool ok = true;
        for (int k = 0; k < n; k++) {
          if (active[k].empty()) {
            ok = false;
            break;
          }
        }

        if (ok) {
          for (int k = 0; k < n; k++) {
            auto it = active[k].begin();
            assert(x <= it->first);
            active[k].erase(it);
          }
          assert(x > 0);
          ans++;
        }
      }
    }

    printf("Case #%d: %d\n", t, ans);
  }
  return 0;
}
