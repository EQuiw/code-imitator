#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lp(i, a, n) for (int i = (a); i <= (int)(n); ++i)
#define lpd(i, a, n) for (int i = (a); i >= (int)(n); --i)
#define mem(a, b) memset(a, b, sizeof a)
#define all(v) v.begin(), v.end()
#define println(a) cout << (a) << endl
#define sz(x) ((int)(x).size())
#define readi(x) scanf("%d", &x)
#define read2i(x, y) scanf("%d%d", &x, &y)
#define read3i(x, y, z) scanf("%d%d%d", &x, &y, &z)
#define readll(x) scanf("%I64d", &x)
#define mod 1000000007
#define eps 1e-6
#define infi 1000000000
#define infll 1000000000000000000ll
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

#define MAXN 1002    // maximum number of nodes
int n;               // number of nodes
int cap[MAXN][MAXN]; // capacity
int path[MAXN];
int pathLength;
bool visited[MAXN];

bool intersect(pii a, pii b) {
  return (a.f >= b.f and a.f <= b.s) or (a.s >= b.f and a.s <= b.s);
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
      if (!intersect(interval[pos.f][pos.s], currentInterval))
        continue;
    }

    ret = getPath(i, TargetNode, curLen + 1, min(maxcap, cap[StartNode][i]),
                  mp(max(currentInterval.f, interval[pos.f][pos.s].f),
                     min(currentInterval.s, interval[pos.f][pos.s].s)));

    if (ret > 0)
      break; // We found a path with flow
  }
  return ret;
}

int maxFlow(int src, int sink, int numberOfNodes) {
  int total_flow = 0;
  n = numberOfNodes;

  while (1) {
    mem(visited, 0);
    int newflow = getPath(src, sink, 0, infi, mp(-infi, infi));

    if (!newflow)
      break; // once no more paths, STOP

    lp(i, 1, pathLength - 1) {
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
  if (a[i][j] + eps >= 0.9 * mx and a[i][j] - eps <= 1.1 * mx)
    return true;
  mx = a[i][j] / needed[i] * needed[i] - needed[i];
  if (a[i][j] + eps >= 0.9 * mx and a[i][j] - eps <= 1.1 * mx)
    return true;
  mx = a[i][j] / needed[i] * needed[i] + needed[i];
  if (a[i][j] + eps >= 0.9 * mx and a[i][j] - eps <= 1.1 * mx)
    return true;
  return false;
}

int main() {
  freopen("B-small-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);

  readi(t);
  lp(test, 1, t) {
    int n, m;
    read2i(n, m);
    lp(i, 1, n) readi(needed[i]);
    lp(i, 1, n) lp(j, 1, m) {
      readi(a[i][j]);
      interval[i][j] =
          mp(ceil(a[i][j] / 1.1 / needed[i]), a[i][j] / 0.9 / needed[i]);
      id[i][j] = ++uniq;
      intervalByID[id[i][j]] = mp(i, j);
    }
    intervalByID[0] = mp(-infi, infi);

    lp(i, 1, n - 1) lp(j, 1, m) if (check(i, j))
        lp(k, 1, m) if (check(i + 1, k)) {
      if (intersect(interval[i][j], interval[i + 1][k]))
        cap[id[i][j]][id[i + 1][k]] = 1;
    }

    lp(j, 1, m) {
      if (check(1, j))
        cap[0][id[1][j]] = 1;
      if (check(n, j))
        cap[id[n][j]][n * m + 1] = 1;
    }
    printf("Case #%d: %d\n", test, maxFlow(0, n * m + 1, n * m));

    uniq = 0;
    mem(cap, 0);
  }
}

// freopen("input.txt","r",stdin);
// freopen("output.txt","w",stdout);
// ios::sync_with_stdio(0);cin.tie(0);
