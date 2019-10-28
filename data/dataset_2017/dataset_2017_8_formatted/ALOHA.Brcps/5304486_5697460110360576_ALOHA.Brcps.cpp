#include <algorithm>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

pair<int, int> getRange(int need, int available) {
  available *= 10;

  int maximum = available / (9 * need);
  int minimum = available / (11 * need);

  if (available % (11 * need) != 0) {
    minimum++;
  }

  if (maximum < minimum) {
    return make_pair(-1, -1);
  }

  return make_pair(minimum, maximum);
}

int main() {
  int T;
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);

  scanf("%d", &T);

  for (int testCase = 1; testCase <= T; testCase++) {
    int N, P;
    scanf("%d %d", &N, &P);

    int pack[100][100];
    int needs[100];

    int idx[100] = {
        0,
    };

    pair<int, int> rng[100][100];

    for (int i = 0; i < N; i++) {
      scanf("%d", &needs[i]);
    }

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < P; j++) {
        scanf("%d", &pack[i][j]);
      }
    }

    for (int i = 0; i < N; i++) {
      sort(pack[i], pack[i] + P);
    }

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < P; j++) {
        rng[i][j] = getRange(needs[i], pack[i][j]);
      }
    }

    int res = 0;

    for (; idx[0] < P; idx[0]++) {
      int minimum = rng[0][idx[0]].first;
      bool ck = true;

      if (minimum == -1)
        continue;

      do {
        for (int j = 1; j < N; j++) {
          for (; idx[j] < P; idx[j]++) {
            if (minimum <= rng[j][idx[j]].second) {
              minimum = max(minimum, rng[j][idx[j]].first);
              break;
            }
          }

          if (idx[j] >= P) {
            goto EXIT;
          }
        }

        for (int j = 0; j < N; j++) {
          if (rng[j][idx[j]].first <= minimum &&
              minimum <= rng[j][idx[j]].second) {
            continue;
          } else {
            ck = false;
            break;
          }
        }
      } while (minimum <= rng[0][idx[0]].second && !ck);

      if (ck) {
        res++;
        for (int j = 1; j < N; j++) {
          idx[j]++;

          if (idx[j] >= P) {
            break;
          }
        }
      }
    }
  EXIT:

    printf("Case #%d: %d\n", testCase, res);
  }

  return 0;
}