/******************************************
 *    AUTHOR:         BHUVNESH JAIN        *
 *    INSTITUITION:   BITS PILANI, PILANI  *
 ******************************************/
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef long double LD;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;

char mp[7] = "RYBOGV";

int main() {
  int t;
  scanf("%d", &t);
  for (int T = 1; T <= t; ++T) {
    printf("Case #%d: ", T);
    int n, r, o, y, g, b, v;
    scanf("%d %d %d %d %d %d %d", &n, &r, &o, &y, &g, &b, &v);
    vector<int> p(n, -1);
    vector<pii> x;
    x.push_back({r, 0});
    x.push_back({y, 1});
    x.push_back({b, 2});
    sort(x.begin(), x.end());
    reverse(x.begin(), x.end());
    int can = 0;
    for (int i = 0; i < n; i += 2) {
      p[i] = x[0].second;
      can += 1;
      if (can == x[0].first) {
        break;
      }
    }
    vector<int> pos;
    for (int i = 0; i < n; ++i) {
      if (p[i] == -1) {
        pos.push_back(i);
      }
    }
    if (can < x[0].first) {
      printf("IMPOSSIBLE\n");
    } else {
      int turn = 1, val = x[1].first, val2 = x[2].first;
      for (int i : pos) {
        if ((turn && val > 0) || val2 <= 0) {
          p[i] = x[1].second;
          val -= 1;
          if (val <= val2) {
            turn ^= 1;
          }
        } else {
          p[i] = x[2].second;
          val2 -= 1;
          if (val2 <= val) {
            turn ^= 1;
          }
        }
      }
      bool ans = 1;
      for (int i = 0; i < n; ++i) {
        if (p[i] == p[(i + 1) % n] || p[i] == p[(i - 1 + n) % n]) {
          ans = 0;
          break;
        }
      }
      int cnt[3] = {0, 0, 0};
      for (int i = 0; i < n; ++i) {
        cnt[p[i]] += 1;
      }
      for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
          if (x[j].second == i) {
            assert(cnt[i] == x[j].first);
          }
        }
      }
      if (ans) {
        for (int i = 0; i < n; ++i) {
          printf("%c", mp[p[i]]);
        }
        printf("\n");
      } else {
        cerr << "came\n" << r << " " << y << " " << b << "\n";
        printf("IMPOSSIBLE\n");
      }
    }
  }
  return 0;
}
