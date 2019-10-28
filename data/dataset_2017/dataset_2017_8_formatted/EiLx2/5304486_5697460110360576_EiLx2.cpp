#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

#define fi first
#define se second
typedef long long LL;
typedef long double LD;

struct range {
  int l, r;
  range() {}
  range(int l, int r) : l(l), r(r) {}
};

struct point {
  int x, type, ind;
  bool e;

  point() {}
  point(int x, int type, int ind, bool e) : x(x), type(type), ind(ind), e(e) {}
};

LL T, N, P, req[110], a[110][110], K;
range r[110][110];
point p[10000];

int cnt[110], tot;
bool act[110][110];

void rmv(int type, int ind) {
  if (act[type][ind] == 0)
    return;
  act[type][ind] = 0;
  cnt[type]--;
  if (cnt[type] == 0)
    tot--;
}

void add(int type, int ind) {
  act[type][ind] = 1;
  cnt[type]++;
  if (cnt[type] == 1)
    tot++;
}

int main() {
  ifstream fin("input.in");
  ofstream fout("output.out");
  fin >> T;

  int i, t, j, k;
  for (t = 1; t <= T; t++) {
    fout << "Case #" << t << ": ";
    fin >> N >> P;
    for (i = 1; i <= N; i++)
      fin >> req[i];

    int L, R;
    K = 0;
    memset(p, 0, sizeof(p));
    memset(cnt, 0, sizeof(cnt));
    memset(act, 0, sizeof(act));
    tot = 0;

    for (i = 1; i <= N; i++)
      for (j = 1; j <= P; j++) {
        fin >> a[i][j];
        L = (100 * a[i][j] + 110 * req[i] - 1) / (110 * req[i]);
        R = (100 * a[i][j]) / (90 * req[i]);
        if (L <= R) {
          r[i][j] = range(L, R);
          p[++K] = point(L, i, j, 0);
          p[++K] = point(R, i, j, 1);
        }
      }

    sort(p + 1, p + K + 1, [](point A, point B) {
      if (A.x == B.x)
        return (A.e < B.e);
      else
        return (A.x < B.x);
    });
    tot = 0;
    int res = 0;
    memset(cnt, 0, sizeof(cnt));
    for (k = 1; k <= K; k++) {
      if (p[k].e) {
        rmv(p[k].type, p[k].ind);
      } else {
        add(p[k].type, p[k].ind);
        if (tot == N) {
          for (i = 1; i <= N; i++) {
            int pos = -1;
            for (j = 1; j <= P; j++)
              if (act[i][j]) {
                if (pos == -1)
                  pos = j;
                else if (r[i][j].r < r[i][pos].r)
                  pos = j;
              }

            rmv(i, pos);
          }

          res++;
        }
      }
    }

    fout << res << "\n";
  }
  return 0;
}
