#include <bits/stdc++.h>

using namespace std;

struct compare {
  bool operator()(const pair<int, int> &lhs, const pair<int, int> &rhs) const {
    return lhs.first > rhs.first;
  }
};
multiset<pair<int, int>, compare> S;
int q, n, k;

int main() {

  scanf("%d", &q);
  for (int t = 1; t <= q; ++t) {
    scanf("%d %d", &n, &k);
    S.clear();
    S.insert(make_pair(n, 1));
    int times = log(k) / log(2);
    int l = 0;
    int r = n + 1;
    int m = n;
    int Pow = 1;
    int cnt = 0;
    int vmin = 0;
    int vmax = 0;
    for (int kk = 1; kk <= times; kk++) {
      int xx = 0;
      int yy = 0;
      for (int j = 1; j <= Pow; j += yy) {
        xx = (*S.begin()).first;
        yy = (*S.begin()).second;
        S.erase(S.begin());
        xx--;
        k -= yy;

        if (xx == 0) {
          vmin = vmax = 0;
          continue;
        }

        if (xx & 1) {
          S.insert(make_pair(xx / 2, yy));
          S.insert(make_pair(xx - (xx / 2), yy));
          vmax = max(xx / 2, xx - (xx / 2));
          vmin = min(xx / 2, xx - (xx / 2));
        } else {
          S.insert(make_pair(xx / 2, yy * 2));
          vmin = vmax = xx / 2;
        }
      }
      Pow *= 2;
    }
    while (k) {
      int xx = (*S.begin()).first;
      int yy = (*S.begin()).second;
      if (yy <= k) {
        k -= yy;
        xx--;
        S.erase(S.begin());
        if (xx == 0) {
          vmin = vmax = 0;
          continue;
        }
        if (xx & 1) {
          S.insert(make_pair(xx / 2, yy));
          S.insert(make_pair(xx - (xx / 2), yy));
          vmax = max(xx / 2, xx - (xx / 2));
          vmin = min(xx / 2, xx - (xx / 2));
        } else {
          S.insert(make_pair(xx / 2, yy * 2));
          vmax = vmin = xx / 2;
        }
      } else {
        S.erase(S.begin());
        S.insert(make_pair(xx, yy - k));
        xx--;
        if (xx == 0) {
          vmin = vmax = 0;
          continue;
        }
        if (xx & 1) {
          S.insert(make_pair(xx / 2, k));
          S.insert(make_pair(xx - (xx / 2), k));

          vmax = max(xx / 2, xx - (xx / 2));
          vmin = min(xx / 2, xx - (xx / 2));
        } else {
          S.insert(make_pair(xx / 2, k * 2));
          vmax = vmin = xx / 2;
        }
        k = 0;
      }
    }

    printf("Case #%d: %d %d\n", t, vmax, max(0, vmin));
  }
}