#include <cstdio>
#include <cstdlib>

int T, N;
int num[6];
int ans[1005];
int haveAns;
int valid[6][6] = {0};
char m[] = {'R', 'O', 'Y', 'G', 'B', 'V'};

int possible(int n) {
  int bound = n == N ? n / 2 : (n + 1) / 2;
  // red
  if (num[0] + num[1] + num[5] > bound) {
    return 0;
  }
  // yellow
  if (num[1] + num[2] + num[3] > bound) {
    return 0;
  }
  // blue
  if (num[3] + num[4] + num[5] > bound) {
    return 0;
  }
  return 1;
}

void dfs(int layer) {
  if (!possible(N - layer)) {
    return;
  }

  if (layer == N) {
    if (valid[ans[0]][ans[N - 1]]) {
      haveAns = 1;
      return;
    }
  }
  for (int i = 0; i < 6; i++) {
    if ((layer == 0 || valid[ans[layer - 1]][i]) && num[i] > 0) {
      ans[layer] = i;
      num[i]--;
      dfs(layer + 1);
      num[i]++;
      if (haveAns) {
        return;
      }
    }
  }
}

int main() {

  valid[0][2] = valid[0][3] = valid[0][4] = 1;
  valid[2][0] = valid[2][4] = valid[2][5] = 1;
  valid[4][0] = valid[4][1] = valid[4][2] = 1;
  valid[3][0] = valid[1][4] = valid[5][2] = 1;

  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    scanf("%d", &N);
    for (int i = 0; i < 6; i++) {
      scanf("%d", &num[i]);
    }
    haveAns = 0;
    dfs(0);
    printf("Case #%d: ", t);
    if (haveAns) {
      for (int i = 0; i < N; i++) {
        printf("%c", m[ans[i]]);
      }
      printf("\n");
    } else {
      printf("IMPOSSIBLE\n");
    }
  }
  return 0;
}
