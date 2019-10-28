#include <bits/stdc++.h>

using namespace std;

bool ok(int a, int qa) {
  return 0.9 <= (a / (double)qa) && (a / (double)qa) <= 1.1;
}

bool can(int a, int qa) {
  int l = max(1.0, floor(a / (1.1 * qa)) - 3), r = ceil(a / (0.9 * qa)) + 3;
  for (int i = l, __ = r + 1; i < __; ++i) {
    if (ok(a, i * qa))
      return 1;
  }
  return 0;
}

bool can(int a, int qa, int b, int qb) {
  int la = max(1.0, floor(a / (1.1 * qa)) - 3), ra = ceil(a / (0.9 * qa)) + 3,
      lb = max(1.0, floor(b / (1.1 * qb)) - 3), rb = ceil(b / (0.9 * qb)) + 3,
      l = max(la, lb), r = min(ra, rb);
  for (int i = l, __ = r + 1; i < __; ++i) {
    if (ok(a, i * qa) && ok(b, i * qb))
      return 1;
  }
  return 0;
}
int n, p;
int q[111], mat[111][111];

const int mv = 500, me = 50 * 500;
int ant[me], to[me], cap[me], adj[mv], z;

inline void add(int a, int b, int c) {
  // dbg("add" _ a _ b _ c)
  ant[z] = adj[a], to[z] = b, cap[z] = c, adj[a] = z++;
  swap(a, b);
  ant[z] = adj[a], to[z] = b, cap[z] = c, adj[a] = z++;
}

int level[mv], fila[mv], copy_adj[mv];
int bfs(int src, int sink) {
  memset(level, -1, sizeof level);
  level[src] = 0;
  int pos = 0, tam = 0;
  fila[tam++] = src;
  while (pos < tam) {
    int now = fila[pos++];
    for (int i = adj[now]; i != -1; i = ant[i]) {
      if (cap[i] && level[to[i]] == -1) {
        level[to[i]] = level[now] + 1;
        fila[tam++] = to[i];
      }
    }
  }
  return level[sink] != -1;
}

int dfs(int no, int sink, int flow) {
  // dbg(no _ sink _ flow)
  if (no == sink)
    return flow;
  for (int &i = copy_adj[no]; i != -1; i = ant[i]) {
    if (cap[i] && level[no] + 1 == level[to[i]]) {
      int nflow = dfs(to[i], sink, min(flow, cap[i]));
      if (nflow) {
        cap[i] -= nflow, cap[i ^ 1] += nflow;
        return nflow;
      }
    }
  }
  return 0;
}

int maxflow(int src, int sink) {
  int mf = 0;
  while (1) {
    if (bfs(src, sink)) {
      memcpy(copy_adj, adj, sizeof adj);
      while (1) {
        int add = dfs(src, sink, 1 << 30);
        // dbg(add)
        if (add)
          mf += add;
        else
          break;
      }
    } else
      break;
  }
  return mf;
}

int main() {
  ios::sync_with_stdio(0);
  int t, cas = 1;
  cin >> t;
  int src = mv - 5, sink = mv - 4;
  while (t--) {
    memset(adj, -1, sizeof adj);
    z = 0;
    cout << "Case #" << cas++ << ": ";
    cin >> n >> p;
    for (int i = 0, __ = n; i < __; ++i)
      cin >> q[i];
    for (int i = 0, __ = n; i < __; ++i) {
      for (int j = 0, __ = p; j < __; ++j) {
        cin >> mat[i][j];
        add(2 * (i * p + j), 2 * (i * p + j) + 1, 1);
        if (i == 0) {
          add(src, 2 * (i * p + j), 1);
        } else {
          for (int k = 0, __ = p; k < __; ++k) {
            if (can(mat[i - 1][k], q[i - 1], mat[i][j], q[i]))
              add(2 * ((i - 1) * p + k) + 1, 2 * (i * p + j), 1);
          }
        }
        if (i + 1 == n && can(mat[i][j], q[i]))
          add(2 * (i * p + j) + 1, sink, 1);
      }
    }
    cout << maxflow(src, sink) << endl;
  }
  return 0;
}
