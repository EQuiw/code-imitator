#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("B-small.out", "w", stdout);
  int T;
  scanf("%d", &T);
  for (int cn = 1; cn <= T; ++cn) {
    int N, P;
    scanf("%d%d", &N, &P);
    vector<int> R(N);
    vector<vector<int>> Q(N, vector<int>(P, 0));

    for (int i = 0; i < N; ++i)
      scanf("%d", &R[i]);
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < P; ++j)
        scanf("%d", &Q[i][j]);
      sort(Q[i].begin(), Q[i].end());
    }

    vector<pair<int, int>> ret;
    for (int i = 0; i < N; ++i) {
      vector<pair<int, int>> cret, pret;
      for (int j = 0; j < P; ++j) {
        int l = Q[i][j] / (R[i] * 1.1);
        if ((Q[i][j] * 10) % (R[i] * 11) != 0)
          l++;
        int r = Q[i][j] / (R[i] * 0.9);

        if (l <= r)
          cret.push_back({l, r});
      }
      if (i == 0) {
        ret = cret;
      } else {
        pret = ret;
        ret.clear();
        int c = 0, p = 0;
        while (true) {
          if (cret.size() <= c)
            break;
          if (pret.size() <= p)
            break;

          if (max(cret[c].first, pret[p].first) <=
              min(cret[c].second, pret[p].second)) {
            ret.push_back({max(cret[c].first, pret[p].first),
                           min(cret[c].second, pret[p].second)});
            c++;
            p++;
          } else if (cret[c].second > pret[p].second) {
            p++;
          } else {
            c++;
          }
        }
      }
    }
    printf("Case #%d: %d\n", cn, ret.size());
  }
}