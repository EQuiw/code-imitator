#include <algorithm>
#include <queue>
#include <stdio.h>
using namespace std;

int T;
int N, P;
long long int R[100];
long long int Q[100][100];
bool d[2][100][1000001];
int map[1010][1010];
bool chk[1010];
int parent[1010];

int BFS(int src, int dst) {
  int i;
  struct Node {
    int idx, cost;
  };
  queue<Node> que;

  for (i = 0; i < (N * P + 2); i++) {
    chk[i] = false;
    parent[i] = 0;
  }
  que.push({src, 1000000});
  chk[src] = true;
  parent[src] = -1;

  int res = 1000000;
  while (true) {
    if (que.empty())
      break;
    Node current = que.front();
    que.pop();

    if (current.idx == (N * P + 1)) {
      res = current.cost;
      break;
    }
    for (i = 0; i < (N * P + 2); i++) {
      if (map[current.idx][i] > 0 && !chk[i]) {
        que.push({i, min(current.cost, map[current.idx][i])});
        chk[i] = true;
        parent[i] = current.idx;
      }
    }
  }
  if (res != 1000000) {
    int pos = (N * P + 1);
    while (true) {
      if (parent[pos] < 0)
        break;
      map[parent[pos]][pos] -= res;
      map[pos][parent[pos]] += res;
      pos = parent[pos];
    }
  }
  return res;
}
int Solve(int src, int dst) {
  int i, j;
  int sum = 0;
  while (true) {
    int value = BFS(src, dst);
    if (value == 1000000)
      break;
    sum += value;
  }
  return sum;
}
int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int t;
  int i, j, k, l;

  scanf("%d", &T);
  for (t = 1; t <= T; t++) {
    scanf("%d %d", &N, &P);
    for (i = 0; i < N; i++)
      scanf("%lld", &R[i]);
    for (i = 0; i < N; i++) {
      for (j = 0; j < P; j++)
        scanf("%lld", &Q[i][j]);
    }

    for (i = 0; i < (N * P + 2); i++) {
      for (j = 0; j < (N * P + 2); j++)
        map[i][j] = 0;
    }
    for (i = 0; i < P; i++) {
      for (j = 1; j <= 1000000; j++) {
        d[0][i][j] = true;
        d[1][i][j] = false;
      }
    }
    for (i = 0; i < N; i++) {
      for (j = 0; j < P; j++) {
        for (k = 1; k <= 1000000; k++) {
          long long int value = R[i] * k;
          long long int left = value * 9;
          long long int right = value * 11;
          long long int q = Q[i][j] * 10;
          if (left <= q && q <= right)
            d[1][j][k] = true;
        }
      }
      for (j = 0; j < P; j++) {
        for (k = 1; k <= 1000000; k++) {
          if (d[1][j][k]) {
            for (l = 0; l < P; l++) {
              if (d[0][l][k]) {
                if (i == 0)
                  map[(N * P)][i * P + j] = 1;
                else
                  map[(i - 1) * P + l][i * P + j] = 1;
              }
            }
          }
        }
      }
      for (j = 0; j < P; j++) {
        for (k = 1; k <= 1000000; k++) {
          d[0][j][k] = d[1][j][k];
          d[1][j][k] = false;
        }
      }
    }
    for (i = 0; i < P; i++) {
      map[(N - 1) * P + i][(N * P + 1)] = 1;
    }
    printf("Case #%d: %d\n", t, Solve((N * P), (N * P + 1)));
  }
  return 0;
}
