#include <algorithm>
#include <assert.h>
#include <iostream>
#include <map>
#include <queue>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

int main() {
  int T;
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);

  scanf("%d", &T);

  for (int testCase = 1; testCase <= T; testCase++) {
    int N, C, M;
    int seat[1001] = {
        0,
    };
    int each[1001] = {
        0,
    };

    scanf("%d %d %d", &N, &C, &M);
    for (int i = 0; i < M; i++) {
      int P, B;
      scanf("%d %d", &P, &B);

      seat[P]++;
      each[B]++;
    }

    printf("Case #%d: ", testCase);

    int maxTicket = 0;
    for (int i = 1; i <= C; i++) {
      maxTicket = max(maxTicket, each[i]);
    }

    for (int k = maxTicket;; k++) {
      int diff = 0, prom = 0;
      for (int i = N; i >= 1; i--) {
        if (seat[i] > k) {
          diff += seat[i] - k;
          prom += seat[i] - k;
        } else {
          diff -= k - seat[i];
          if (diff < 0) {
            diff = 0;
          }
        }
      }

      if (diff == 0) {
        printf("%d %d\n", k, prom);
        break;
      }
    }
  }

  return 0;
}
