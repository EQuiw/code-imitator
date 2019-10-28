#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int, int> P;
const LL inf = 1LL << 61;
const LL mod = 1000000007;
const int maxn = 1010;

int main() {
  // std::ios::sync_with_stdio(false);
  int i = 0, j = 0, k = 0, kase = 0;
  int n, t;
  char str[maxn];
  freopen("A-small-attempt1.in", "r", stdin);
  freopen("out.txt", "w", stdout);
  scanf("%d", &t);
  while (t--) {
    int r, c;
    char cake[30][30];
    scanf("%d%d", &r, &c);
    getchar();
    for (i = 0; i < r; i++) {
      for (j = 0; j < c; j++) {
        scanf("%c", &cake[i][j]);
      }
      getchar();
    }
    int zero_flag = -1;
    bool meet_flag = false;
    for (i = 0; i < r; i++) {
      int cpos = -1;
      for (j = 0; j < c; j++) {
        if (cake[i][j] != '?') {
          cpos = j;
          break;
        }
      }
      if (cpos == -1) {
        if (!meet_flag) {
          zero_flag++;
          continue;
        }
        for (j = 0; j < c; j++) {
          cake[i][j] = cake[i - 1][j];
        }
      } else {
        meet_flag = true;
        for (j = 0; j < cpos; j++) {
          cake[i][j] = cake[i][cpos];
        }
        for (j = cpos + 1; j < c; j++) {
          if (cake[i][j] == '?')
            cake[i][j] = cake[i][j - 1];
        }
      }
    }
    if (zero_flag >= 0) {
      for (i = zero_flag; i >= 0; i--) {
        for (j = 0; j < c; j++) {
          cake[i][j] = cake[i + 1][j];
        }
      }
    }
    printf("Case #%d:\n", ++kase);
    for (i = 0; i < r; i++) {
      for (j = 0; j < c; j++) {
        printf("%c", cake[i][j]);
      }
      printf("\n");
    }
  }

  return 0;
}
