#include <iostream>
#include <queue>
#include <stdio.h>
#include <vector>
using namespace std;

struct H {
  double dis, speed;
};
struct Node {
  int idx;
  double cost;
};
struct QUE {
  int pos;
  double time;
  double dis;
  double speed;

  bool operator<(const QUE &rhs) const { return time > rhs.time; }
};
int T;
int N, Q;
H h[101];
vector<Node> list[101];

double Solve(int src, int dst) {
  int i;

  priority_queue<QUE> que;
  que.push({src, 0, h[src].dis, h[src].speed});

  while (true) {
    if (que.empty())
      break;
    QUE current = que.top();
    que.pop();

    if (current.pos == dst)
      return current.time;

    for (i = 0; i < list[current.pos].size(); i++) {
      int dst = list[current.pos][i].idx;
      double cost = list[current.pos][i].cost;
      if (current.dis >= cost) {
        que.push({dst, current.time + cost / current.speed, current.dis - cost,
                  current.speed});
      }
      if (h[current.pos].dis >= cost) {
        que.push({dst, current.time + cost / h[current.pos].speed,
                  h[current.pos].dis - cost, h[current.pos].speed});
      }
    }
  }
  return 0;
}
int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int t;
  int i, j;
  double x;
  int s, e;

  scanf("%d", &T);
  for (t = 1; t <= T; t++) {
    scanf("%d %d", &N, &Q);
    for (i = 1; i <= N; i++)
      scanf("%lf %lf", &h[i].dis, &h[i].speed);

    for (i = 1; i <= N; i++)
      list[i].clear();
    for (i = 1; i <= N; i++) {
      for (j = 1; j <= N; j++) {
        scanf("%lf", &x);
        if (x >= 0)
          list[i].push_back({j, x});
      }
    }
    printf("Case #%d:", t);
    for (i = 0; i < Q; i++) {
      scanf("%d %d", &s, &e);
      printf(" %lf", Solve(s, e));
    }
    printf("\n");
  }
  return 0;
}
