#include <algorithm>
#include <assert.h>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <math.h>
#include <memory.h>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> Pi;
int N, M, K, tc;
char p[40][40];

void solve() {
  scanf("%d%d", &N, &M);
  for (int i = 1; i <= N; i++)
    scanf("%s", p[i] + 1);

  for (int i = 1; i <= N; i++) {
    for (int j = 2; j <= M; j++) {

      if (p[i][j] == '?') {
        if (p[i][j - 1] != '?') {
          p[i][j] = p[i][j - 1];
        }
      }
    }
  }

  for (int i = 1; i <= N; i++) {
    for (int j = M - 1; j >= 1; j--) {
      if (p[i][j] == '?') {
        if (p[i][j + 1] != '?') {
          p[i][j] = p[i][j + 1];
        }
      }
    }
  }

  for (int j = 1; j <= M; j++) {
    for (int i = 2; i <= N; i++) {
      if (p[i][j] == '?') {
        if (p[i - 1][j] != '?') {
          p[i][j] = p[i - 1][j];
        }
      }
    }
  }

  for (int j = 1; j <= M; j++) {
    for (int i = N - 1; i >= 1; i--) {
      if (p[i][j] == '?') {
        if (p[i + 1][j] != '?') {
          p[i][j] = p[i + 1][j];
        }
      }
    }
  }
  printf("\n");
  for (int i = 1; i <= N; i++)
    printf("%s\n", p[i] + 1);
}

int main(void) {
  freopen("output.txt", "w", stdout);
  scanf("%d", &tc);
  for (int t = 1; t <= tc; t++) {
    printf("Case #%d: ", t);
    solve();
  }
}
