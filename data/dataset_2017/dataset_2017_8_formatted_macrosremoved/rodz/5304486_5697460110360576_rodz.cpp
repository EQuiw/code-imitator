#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int N = 52;
int need[N];
int inter[N][N][2];

struct event {
  int x, ingr, type, idx;
  event() {}
  event(int x, int ingr, int type, int idx)
      : x(x), ingr(ingr), type(type), idx(idx) {}
  bool operator<(const event &e) {
    if (x == e.x)
      return type < e.type;
    return x < e.x;
  }
};

int main() {
  int t, casecnt = 1;
  scanf("%d", &t);
  while (t--) {
    int n, p;
    scanf("%d %d", &n, &p);
    printf("Case #%d: ", casecnt++);
    for (int i = 0; i < n; i++)
      scanf("%d", need + i);

    vector<event> ev;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < p; j++) {
        int x;
        int y = need[i];
        scanf("%d", &x);
        int lo = 10 * x / (11 * y);
        if ((10 * x) % (11 * y))
          lo++;
        int hi = 10 * x / (9 * y);
        inter[i][j][0] = lo;
        inter[i][j][1] = hi;
        if (hi >= lo) {
          ev.push_back(event(lo, i, 0, j));
          ev.push_back(event(hi, i, 1, j));
        }
      }
    }
    sort(ev.begin(), ev.end());
    set<ii> s[N];
    int cnt = 0;
    int ans = 0;
    for (int i = 0; i < ev.size(); i++) {
      if (ev[i].type == 0) {
        s[ev[i].ingr].insert(ii(inter[ev[i].ingr][ev[i].idx][1], ev[i].idx));
        if (s[ev[i].ingr].size() == 1)
          cnt++;

        if (cnt == n) {
          ans++;
          for (int i = 0; i < n; i++) {
            s[i].erase(s[i].begin());
            if (s[i].empty())
              cnt--;
          }
        }
      } else {
        if (!s[ev[i].ingr].count(
                ii(inter[ev[i].ingr][ev[i].idx][1], ev[i].idx)))
          continue;

        s[ev[i].ingr].erase(ii(inter[ev[i].ingr][ev[i].idx][1], ev[i].idx));
        if (s[ev[i].ingr].size() == 0)
          cnt--;
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
