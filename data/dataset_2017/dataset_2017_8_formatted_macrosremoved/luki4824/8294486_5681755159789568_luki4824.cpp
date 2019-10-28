#include <algorithm>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;
struct Node {
  bool vis;
  vector<pair<int, double>> edges;
  double entertime;
  double dis, speed;
};
struct horse {
  double time;
  double dis;
  int node;
  double speed;
  bool operator<(horse a) const {
    if (a.time < time)
      return true;
    return false;
  }
};
Node graph[101];
int n, q;
void clear() {
  for (int i = 0; i < 101; ++i) {
    // graph[i].dis = 0;
    // graph[i].edges.clear();
    graph[i].vis = false;
    graph[i].entertime = -1;
  }
}
double di(int b, int e) {
  graph[b].entertime = 0;
  priority_queue<horse> que;
  horse h;

  h.dis = graph[b].dis;
  h.time = 0;
  h.speed = graph[b].speed;
  h.node = b;
  que.push(h);
  while (!que.empty()) {
    h = que.top();
    que.pop();
    if (h.node == e)
      return h.time;
    if (!graph[h.node].vis && h.node != b) {
      horse a;
      a.time = h.time;
      a.dis = graph[h.node].dis;
      a.speed = graph[h.node].speed;
      a.node = h.node;
      que.push(a);
      graph[h.node].vis = true;
    }
    for (auto it : graph[h.node].edges) {
      if (it.second <= h.dis) {
        horse a;
        a.dis = h.dis - it.second; // -h.dis;
        a.node = it.first;
        a.speed = h.speed;
        a.time = h.time + it.second / h.speed;
        que.push(a);
        if (graph[it.first].entertime == -1)
          graph[it.first].entertime = a.time;
        graph[it.first].entertime = min(graph[it.first].entertime, a.time);
      }
    }
  }
}
void solve() {
  int a, b;
  while (q--) {
    clear();
    cin >> a >> b;
    cout << setprecision(9) << di(a, b) << " ";
  }

  cout << "\n";
}
void input() {
  double a;
  cin >> n >> q;
  for (int i = 1; i <= n; ++i)
    cin >> graph[i].dis >> graph[i].speed;
  for (int i = 1; i <= n; ++i) {
    graph[i].edges.clear();
    for (int j = 1; j <= n; ++j) {
      cin >> a;
      if (a != -1) {
        graph[i].edges.push_back(make_pair(j, a));
      }
    }
  }
}
int main() {
  int t, m, n;
  cin >> t;
  for (int k = 1; k <= t; ++k) {
    clear();
    input();
    printf("Case #%d: ", k);
    solve();
  }
}
