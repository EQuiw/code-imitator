#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define re(i, a, b) for (int i = a; i <= b; i++)
#define rep(i, a, b) for (int i = a; i >= b; i--)
#define MAX 20000000000000
using namespace std;
int T;
int N;
double D;
double k[1010], s[1010];
int ord[1010];
double t0[1010], res;
int cmp(int a, int b) { return s[a] > s[b]; }
double themin(double a, double b) {
  if (a < b)
    return a;
  return b;
}
int main() {
  //	freopen("A.in","r",stdin);freopen("A.out","w",stdout);
  scanf("%d", &T);
  re(casen, 1, T) {
    scanf("%lf%d", &D, &N);
    re(i, 0, N - 1) {
      scanf("%lf%lf", &k[i], &s[i]);
      ord[i] = i;
      t0[i] = MAX;
    }
    sort(ord, ord + N, cmp);
    re(i, 0, N - 1) re(
        j, 0, N - 1) if (i != j) if (s[ord[i]] > s[ord[j]] &&
                                     k[ord[i]] < k[ord[j]] &&
                                     (k[ord[i]] * (s[ord[i]] - s[ord[j]]) +
                                          s[ord[i]] * (k[ord[j]] - k[ord[i]]) <=
                                      D * (s[ord[i]] - s[ord[j]]))) {
      t0[ord[i]] =
          themin(t0[ord[j]], (k[ord[j]] - k[ord[i]]) / (s[ord[i]] - s[ord[j]]));
    }
    res = MAX;
    re(i, 0, N - 1) if (t0[i] != MAX) res = themin(res, k[i] / t0[i] + s[i]);
    else res = themin(res, D * s[i] / (D - k[i]));
    printf("Case #%d: %.6f\n", casen, res);
  }
  //	fclose(stdin);fclose(stdout);
  return 0;
}
