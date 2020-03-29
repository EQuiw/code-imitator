#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

#define INF 987654321

typedef long long lld;

int main() {
  int T;
  freopen("C-small-1-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);

  scanf("%d", &T);

  for (int testCase = 1; testCase <= T; testCase++) {
    int N, K;

    scanf("%d %d", &N, &K);

    double U;
    scanf("%lf", &U);

    double P[51];

    double sum = U;
    for (int i = 0; i < N; i++) {
      scanf("%lf", &P[i]);
      sum += P[i];
    }

    sum /= N;

    printf("Case #%d: ", testCase);

    printf("%lf\n", pow(sum, N));
  }

  return 0;
}