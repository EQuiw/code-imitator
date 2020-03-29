

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

typedef long long lld;

int DP[800][800][3];
int path[800][800][3];
int timeList[2000];

int solve(int CMin, int JMin, int last) {
  if (CMin < 0 || JMin < 0 || timeList[CMin + JMin] == last) {
    return 987654321;
  }

  if (CMin == 0 && JMin == 0) {
    return 0;
  }

  if (DP[CMin][JMin][last] != -1) {
    assert(DP[CMin][JMin][last] >= 0);
    return DP[CMin][JMin][last];
  }

  int &res = DP[CMin][JMin][last];

  res = 987654321;

  if (last == 1) {
    int T1 = solve(CMin - 1, JMin, 1), T2 = solve(CMin - 1, JMin, 2) + 1;

    if (T1 < T2) {
      path[CMin][JMin][last] = 1;
      res = T1;
    } else {
      path[CMin][JMin][last] = 2;
      res = T2;
    }
  } else {
    int T1 = solve(CMin, JMin - 1, 1) + 1, T2 = solve(CMin, JMin - 1, 2);

    if (T1 < T2) {
      path[CMin][JMin][last] = 1;
      res = T1;
    } else {
      path[CMin][JMin][last] = 2;
      res = T2;
    }
  }

  assert(res >= 0);
  assert(CMin >= 0);
  assert(JMin >= 0);
  assert(last == 1 || last == 2);
  return res;
}

int main() {
  int T;
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);

  scanf("%d", &T);

  for (int testCase = 1; testCase <= T; testCase++) {
    int C, J;

    scanf("%d %d", &C, &J);

    memset(DP, -1, sizeof(DP));
    memset(timeList, 0, sizeof(timeList));

    for (int i = 0; i < C; i++) {
      int S, E;
      scanf("%d %d", &S, &E);

      if (S == 0)
        timeList[1440] = 1;

      for (int j = S; j < E; j++) {
        timeList[j] = 1;
      }
    }

    for (int i = 0; i < J; i++) {
      int S, E;
      scanf("%d %d", &S, &E);

      if (S == 0)
        timeList[1440] = 2;

      for (int j = S; j < E; j++) {
        timeList[j] = 2;
      }
    }

    printf("Case #%d: ", testCase);

    int T1 = solve(720, 720, 1), T2 = solve(720, 720, 2);

    int nowC, nowJ, last;
    nowC = nowJ = 720;
    last = 1;

    while (nowC + nowJ > 0) {
      int nextLast;

      nextLast = path[nowC][nowJ][last];
      if (last == 1) {
        nowC--;
      } else {
        nowJ--;
      }

      last = nextLast;
    }

    if (last != 1) {
      T1++;
    }

    nowC = nowJ = 720;
    last = 2;

    while (nowC + nowJ > 0) {
      int nextLast;

      nextLast = path[nowC][nowJ][last];
      if (last == 1) {
        nowC--;
      } else {
        nowJ--;
      }

      last = nextLast;
    }

    if (last != 2) {
      T2++;
    }

    printf("%d\n", min(T1, T2));
  }

  return 0;
}
