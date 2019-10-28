#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;
int T;
int N, Q;
double e[1010], s[1010];
double dist[1010], tmp;
double f[1010], cnt;
int main() {
  //	freopen("C.in","r",stdin);freopen("C.out","w",stdout);
  scanf("%d", &T);
  for (int casen = 1; casen <= T; casen++) {
    scanf("%d%d", &N, &Q);
    for (int i = 0; i <= N - 1; i++) {
      scanf("%lf%lf", &e[i], &s[i]);
      f[i] = 20000000000000;
    }
    for (int i = 0; i <= N - 1; i++)
      for (int j = 0; j <= N - 1; j++) {
        scanf("%lf", &tmp);
        if (i + 1 == j)
          dist[j] = tmp;
      }
    scanf("%lf", &tmp);
    scanf("%lf", &tmp);
    dist[0] = 0;
    f[0] = 0;
    for (int i = 0; i <= N - 2; i++) {
      cnt = 0;
      for (int j = i + 1; j <= N - 1; j++) {
        cnt += dist[j];
        if (cnt > e[i])
          break;
        if (cnt / s[i] + f[i] < f[j])
          f[j] = cnt / s[i] + f[i];
      }
    }
    printf("Case #%d: %.9lf\n", casen, f[N - 1]);
  }
  //	fclose(stdin);fclose(stdout);
  return 0;
}
