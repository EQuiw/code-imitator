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

const int MAX = 1e3 + 3;

vector<pll> go;
LL timer[MAX];

bool cmp(pll a, pll b) {
  if (a.first == b.first) {
    return a.second > b.second;
  }
  return a.first > b.first;
}

int main() {
  int t;
  scanf("%d", &t);
  for (int T = 1; T <= t; ++T) {
    printf("Case #%d: ", T);
    long long d;
    int n;
    scanf("%lld %d", &d, &n);
    go.resize(n);
    for (int i = 0; i < n; ++i) {
      scanf("%lld %lld", &go[i].first, &go[i].second);
    }
    sort(go.begin(), go.end(), cmp);
    LD tx = 1;
    if (n == 1) {
      tx = (d - go[0].first) / ((LD)go[0].second);
    } else {
      if (go[0].second >= go[1].second) {
        tx = (d - go[1].first) / ((LD)go[1].second);
      } else {
        LD meet =
            (go[0].first - go[1].first) / ((LD)go[1].second - (LD)go[0].second);
        meet *= go[0].second;
        meet += go[0].first;
        // printf("%Lf\n", meet);
        if (meet >= d) {
          tx = max((d - go[1].first) / ((LD)go[1].second),
                   (d - go[0].first) / ((LD)go[0].second));
        } else {
          tx = (d - meet) / ((LD)go[0].second);
          // printf("%Lf ", tx);
          tx += (go[0].first - go[1].first) /
                ((LD)go[1].second - (LD)go[0].second);
          // printf("%Lf\n", tx);
        }
      }
    }
    LD ans = d;
    ans /= (LD)tx;
    printf("%.12Lf\n", ans);
  }
  return 0;
}