#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

#define maxn 60
#define LL long long

int N, P;
LL R[maxn], Q[maxn][maxn];
int pos[maxn];

int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("B-small-attempt0.out", "w", stdout);
  int T, num = 0;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &N, &P);
    for (int i = 1; i <= N; i++)
      scanf("%lld", &R[i]);
    for (int i = 1; i <= N; i++)
      for (int j = 1; j <= P; j++)
        scanf("%lld", &Q[i][j]);
    for (int i = 1; i <= N; i++)
      sort(Q[i] + 1, Q[i] + P + 1);
    int cnt = 1;
    for (int i = 2; i <= N; i++)
      if (Q[i][P] / R[i] > Q[cnt][P] / R[cnt])
        cnt = i;
    for (int i = 1; i <= N; i++)
      pos[i] = 1;
    LL lim = Q[cnt][P] / R[cnt] + 1LL, ans = 0;
    for (LL now = 1; now <= lim; now++) {
      bool flag = true;
      while (flag) {
        for (int i = 1; i <= N; i++) {
          LL dLim = ceil(R[i] * now * 0.9), uLim = floor(R[i] * now * 1.1);
          while (pos[i] <= P && Q[i][pos[i]] <= uLim && Q[i][pos[i]] < dLim)
            pos[i]++;
          if (pos[i] > P || Q[i][pos[i]] > uLim)
            flag = false;
        }
        if (flag) {
          ans++;
          for (int i = 1; i <= N; i++)
            pos[i]++;
        }
      }
    }
    printf("Case #%d: %lld\n", ++num, ans);
  }
}
