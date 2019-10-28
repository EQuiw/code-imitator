#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vll;
typedef set<int> si;
typedef map<int, int> mii;

const int N = 52;
int t, a[N][N], needed[N], id[N][N], uniq;
pii interval[N][N], intervalByID[N * N + 10];

int n; // number of nodes
int cap[1002 /* maximum number of nodes*/]
       [1002 /* maximum number of nodes*/]; // capacity
int path[1002 /* maximum number of nodes*/];
int pathLength;
bool visited[1002 /* maximum number of nodes*/];

bool intersect(pii a, pii b) {
  return (a.first >= b.first and a.first <= b.second) or
         (a.second >= b.first and a.second <= b.second);
}

// Implement in anyway that get a path: DFS, BFS, Dijkstra...whatever
int getPath(int StartNode, int TargetNode, int curLen, int maxcap,
            pii currentInterval) {
  path[curLen] = StartNode;
  if (StartNode == TargetNode) {
    pathLength = curLen + 1;
    return maxcap;
  }

  int ret = 0;
  visited[StartNode] = true;

  for (int i = 0; i <= n + 1; i++) {
    if (visited[i] || cap[StartNode][i] <= 0)
      continue;
    pii pos = intervalByID[i];
    if (i and i <= n) {
      if (!intersect(interval[pos.first][pos.second], currentInterval))
        continue;
    }

    ret = getPath(i, TargetNode, curLen + 1, min(maxcap, cap[StartNode][i]),
                  make_pair(max(currentInterval.first,
                                interval[pos.first][pos.second].first),
                            min(currentInterval.second,
                                interval[pos.first][pos.second].second)));

    if (ret > 0)
      break; // We found a path with flow
  }
  return ret;
}

int maxFlow(int src, int sink, int numberOfNodes) {
  int total_flow = 0;
  n = numberOfNodes;

  while (1) {
    memset(visited, 0, sizeof visited);
    int newflow =
        getPath(src, sink, 0, 1000000000, make_pair(-1000000000, 1000000000));

    if (!newflow)
      break; // once no more paths, STOP

    for (int i = (1); i <= (int)(pathLength - 1); ++i) {
      int m = path[i - 1], n = path[i];

      cap[m][n] -= newflow;
      cap[n][m] += newflow; // Add reversed edge
    }
    total_flow += newflow;
  }

  return total_flow;
}

bool check(int i, int j) {
  int mx = a[i][j] / needed[i] * needed[i];
  if (a[i][j] + 1e-6 >= 0.9 * mx and a[i][j] - 1e-6 <= 1.1 * mx)
    return true;
  mx = a[i][j] / needed[i] * needed[i] - needed[i];
  if (a[i][j] + 1e-6 >= 0.9 * mx and a[i][j] - 1e-6 <= 1.1 * mx)
    return true;
  mx = a[i][j] / needed[i] * needed[i] + needed[i];
  if (a[i][j] + 1e-6 >= 0.9 * mx and a[i][j] - 1e-6 <= 1.1 * mx)
    return true;
  return false;
}

int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);

  scanf("%d", &t);
  for (int test = (1); test <= (int)(t); ++test) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = (1); i <= (int)(n); ++i)
      scanf("%d", &needed[i]);
    for (int i = (1); i <= (int)(n); ++i)
      for (int j = (1); j <= (int)(m); ++j) {
        scanf("%d", &a[i][j]);
        interval[i][j] = make_pair(ceil(a[i][j] / 1.1 / needed[i]),
                                   a[i][j] / 0.9 / needed[i]);
        id[i][j] = ++uniq;
        intervalByID[id[i][j]] = make_pair(i, j);
      }
    intervalByID[0] = make_pair(-1000000000, 1000000000);

    for (int i = (1); i <= (int)(n - 1); ++i)
      for (int j = (1); j <= (int)(m); ++j)
        if (check(i, j))
          for (int k = (1); k <= (int)(m); ++k)
            if (check(i + 1, k)) {
              if (intersect(interval[i][j], interval[i + 1][k]))
                cap[id[i][j]][id[i + 1][k]] = 1;
            }

    for (int j = (1); j <= (int)(m); ++j) {
      if (check(1, j))
        cap[0][id[1][j]] = 1;
      if (check(n, j))
        cap[id[n][j]][n * m + 1] = 1;
    }
    printf("Case #%d: %d\n", test, maxFlow(0, n * m + 1, n * m));

    uniq = 0;
    memset(cap, 0, sizeof cap);
  }
}

// freopen("input.txt","r",stdin);
// freopen("output.txt","w",stdout);
// ios::sync_with_stdio(0);cin.tie(0);
