#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int ca;
int n, p;
double c[60], tmp[60];
const double eps = 1e-8;
typedef pair<int, int> pii;
int cl[60];
pii r[60][60];
void init() {
  scanf("%d%d", &n, &p);
  for (int i = 1; i <= n; i++) {
    scanf("%lf", &c[i]);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= p; j++) {
      scanf("%lf", &tmp[j]);
    }
    sort(tmp + 1, tmp + p + 1);
    for (int j = 1; j <= p; j++) {
      r[i][j].first = (int)((tmp[j] * 10 / 11) / c[i] - eps + 1);
      r[i][j].second = (int)((tmp[j] * 10 / 9) / c[i] + eps);
      // cerr << "rr = "<<r[i][j].first <<"  "<<r[i][j].second<<endl;
    }
  }
}
int cnt = 0;
void sov() {
  cnt = 0;
  for (int i = 1; i <= n; i++)
    cl[i] = 1;
  while (1) {
    int l = -1, rr = (1 << 30);
    int fl = 1, minpos = 1;
    for (int ro = 1; ro <= n; ro++) {
      while (r[ro][cl[ro]].first > r[ro][cl[ro]].second) {
        cl[ro]++;
        if (cl[ro] > p)
          return;
      }
      if (r[ro][cl[ro]].first > l) {
        l = r[ro][cl[ro]].first;
      } else
        minpos = ro;
      if (r[ro][cl[ro]].second < rr)
        rr = r[ro][cl[ro]].second;
      if (l > rr) {
        fl = 0;
        break;
      }
    }
    // cerr<<"l  =  "<<l <<"   rr = "<<rr <<endl;
    if (fl == 0) {
      cl[minpos]++;
      if (cl[minpos] > p)
        return;
    } else {
      cnt++;
      for (int i = 1; i <= n; i++) {
        cl[i]++;
        if (cl[i] > p)
          return;
      }
    }
  }
}

int main() {
  int T;
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  scanf("%d", &T);
  for (ca = 1; ca <= T; ca++) {
    init();
    sov();
    printf("Case #%d: %d\n", ca, cnt);
  }
}
