#include <stdio.h>
#include <string.h>

int n, p;
char data[1001];

int main() {
  int i, j, t;

  freopen("output.txt", "w", stdout);
  freopen("input.txt", "r", stdin);

  scanf("%d", &t);

  for (int tt = 1; tt <= t; tt++) {
    scanf(" %s %d", data, &p);
    int answer = 0;
    n = strlen(data);

    for (i = 0; i < n; i++) {
      if (data[i] == '-') {
        if (i + p > n) {
          answer = -1;
          break;
        }
        answer++;
        for (j = i; j < i + p; j++) {
          data[j] = data[j] == '-' ? '+' : '-';
        }
      }
    }
    if (answer == -1) {
      printf("Case #%d: IMPOSSIBLE\n", tt);
    } else {
      printf("Case #%d: %d\n", tt, answer);
    }
  }
  return 0;
}
