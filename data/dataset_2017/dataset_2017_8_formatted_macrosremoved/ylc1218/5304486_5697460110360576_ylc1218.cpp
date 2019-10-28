#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int T, N, P;
int need[10];
int serve[10][10][2];
int ans, used[10], put[10];

void dfs(int layer) {
  if (layer == P) {
    int cnt = 0;
    for (int i = 0; i < P; i++) {
      // printf("(%d - %d)", i, put[i]);
      int p = put[i];
      if (serve[0][i][0] == -1)
        continue;
      if (serve[1][p][0] == -1)
        continue;
      if (serve[0][i][0] > serve[1][p][1] || serve[1][p][0] > serve[0][i][1])
        continue;
      cnt++;
    }
    if (cnt > ans) {
      ans = cnt;
    }
    return;
  }

  for (int i = 0; i < P; i++) {
    if (used[i])
      continue;
    used[i] = 1;
    put[layer] = i;
    dfs(layer + 1);
    used[i] = 0;
  }
}

int main() {
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    scanf("%d %d", &N, &P);
    for (int i = 0; i < N; i++) {
      scanf("%d", &need[i]);
    }

    int have;
    for (int i = 0; i < N; i++) {
      int n = need[i];
      for (int j = 0; j < P; j++) {
        scanf("%d", &have);
        int maxX = floor(have / (0.9 * n));
        int minX = ceil(have / (1.1 * n));

        serve[i][j][0] = serve[i][j][1] = -1;
        for (int x = minX; x <= maxX; x++) {
          double per = ((double)have) / (x * n);
          fprintf(stderr, "per = %lf\n", per);
          if (per >= 0.9 && per <= 1.1) {
            if (serve[i][j][0] == -1) {
              serve[i][j][0] = x;
            }
            serve[i][j][1] = x;
          }
        }
      }
    }

    /*for(int i = 0; i < N; i++){
        for(int j = 0; j < P; j++){
            printf("%d %d\n", serve[i][j][0], serve[i][j][1]);
        }
    }*/

    ans = 0;
    if (N == 1) {
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
          if (serve[i][j][0] != -1) {
            ans++;
          }
        }
      }
    } else if (N == 2) {
      memset(used, 0, sizeof(used));
      dfs(0);
    }
    printf("Case #%d: %d\n", t, ans);
  }

  return 0;
}
