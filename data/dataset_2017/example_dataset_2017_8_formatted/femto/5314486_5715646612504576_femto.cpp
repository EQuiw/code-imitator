#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct edge {
  int src, dst;
  edge(int src, int dst) : src(src), dst(dst) {}
};
typedef vector<edge> edges;
typedef vector<edges> Graph;

#define VAR(x) ((x) << 1)
#define NOT(x) ((x) ^ 1) // !a = NOT(VAR(a))
void visit(int v, const Graph &g, vector<int> &ord, vector<int> &num, int k) {
  if (num[v] >= 0)
    return;
  num[v] = k;
  for (int i = 0; i < g[v].size(); ++i)
    visit(g[v][i].dst, g, ord, num, k);
  ord.push_back(v);
}

typedef pair<int, int> clause; // {a or b}

pair<bool, vector<bool>> two_satisfiability(int m, const vector<clause> &cs) {
  int n = m * 2; // m positive vars and m negative vars
  Graph g(n), h(n);
  for (int i = 0; i < cs.size(); ++i) {
    int u = cs[i].first, v = cs[i].second;
    g[NOT(u)].push_back(edge(NOT(u), v));
    g[NOT(v)].push_back(edge(NOT(v), u));
    h[v].push_back(edge(v, NOT(u)));
    h[u].push_back(edge(u, NOT(v)));
  }
  vector<int> num(n, -1), ord, dro;
  for (int i = 0; i < n; ++i)
    visit(i, g, ord, num, i);
  reverse(ord.begin(), ord.end());
  fill(num.begin(), num.end(), -1);
  for (int i = 0; i < n; ++i)
    visit(ord[i], h, dro, num, i);
  for (int i = 0; i < n; ++i) {
    if (num[i] == num[NOT(i)])
      return {false, vector<bool>()};
  }

  vector<bool> T(m);
  for (int i = 0; i < m; i++) {
    if (num[VAR(i)] > num[NOT(VAR(i))])
      T[i] = 1;
  }
  return {true, T};
}

string b[50];
int R, C;

bool in(int x, int y) { return 0 <= x && x < C && 0 <= y && y < R; }

typedef pair<int, int> P;

int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

bool check(int x, int y, char c) {
  for (int k = 0; k < 4; k++) {
    if ((k == 0 || k == 2) && c == '|')
      continue;
    if ((k == 1 || k == 3) && c == '-')
      continue;
    int nx = x + dx[k], ny = y + dy[k];
    while (in(nx, ny)) {
      if (b[ny][nx] == '-' || b[ny][nx] == '|')
        return true;
      if (b[ny][nx] == '#')
        break;
      nx += dx[k], ny += dy[k];
    }
  }
  return false;
}

int id[50][50];

void solve() {
  cin >> R >> C;
  for (int i = 0; i < R; i++) {
    cin >> b[i];
  }

  int m = 0;
  int mirror = 0;
  vector<P> ps;
  vector<clause> cs;
  for (int y = 0; y < R; y++) {
    for (int x = 0; x < C; x++) {
      if (b[y][x] == '-') {
        if (check(x, y, '|')) {
          cs.push_back({VAR(mirror), VAR(mirror)});
          cs.push_back({NOT(VAR(mirror)), VAR(mirror)});
        }
        if (check(x, y, '-')) {
          cs.push_back({NOT(VAR(mirror)), NOT(VAR(mirror))});
          cs.push_back({VAR(mirror), NOT(VAR(mirror))});
        }
        id[y][x] = mirror++;
        ps.push_back({x, y});
        m++;
      }
      if (b[y][x] == '|') {
        if (check(x, y, '-')) {
          cs.push_back({VAR(mirror), VAR(mirror)});
          cs.push_back({NOT(VAR(mirror)), VAR(mirror)});
        }
        if (check(x, y, '|')) {
          cs.push_back({NOT(VAR(mirror)), NOT(VAR(mirror))});
          cs.push_back({VAR(mirror), NOT(VAR(mirror))});
        }
        id[y][x] = mirror++;
        ps.push_back({x, y});
        m++;
      }
    }
  }

  for (int y = 0; y < R; y++) {
    for (int x = 0; x < C; x++) {
      if (b[y][x] == '.') {
        vector<P> p[2]; // 0 yoko, 1 tate
        for (int k = 0; k < 4; k++) {
          int nx = x + dx[k], ny = y + dy[k];
          while (in(nx, ny)) {
            if (b[ny][nx] == '-' || b[ny][nx] == '|') {
              p[k % 2].push_back({nx, ny});
              break;
            };
            if (b[ny][nx] == '#')
              break;
            nx += dx[k], ny += dy[k];
          }
        }
        if (p[0].size() == 2 || p[1].size() == 2 ||
            p[0].size() + p[1].size() == 0) {
          cout << "IMPOSSIBLE" << endl;
          return;
        }
        if (p[0].size() == 1 && p[1].size() == 0) {
          int nx = p[0][0].first, ny = p[0][0].second;
          int a = VAR(id[ny][nx]);
          if (b[ny][nx] == '|')
            a = NOT(a);
          cs.push_back({a, a});
          cs.push_back({NOT(a), a});
        }
        if (p[0].size() == 0 && p[1].size() == 1) {
          int nx = p[1][0].first, ny = p[1][0].second;
          int a = VAR(id[ny][nx]);
          if (b[ny][nx] == '-')
            a = NOT(a);
          cs.push_back({a, a});
          cs.push_back({NOT(a), a});
        }
        if (p[0].size() == 1 && p[1].size() == 1) {
          int nx1 = p[0][0].first, ny1 = p[0][0].second;
          int a = VAR(id[ny1][nx1]);
          if (b[ny1][nx1] == '|')
            a = NOT(a);
          int nx2 = p[1][0].first, ny2 = p[1][0].second;
          int t = VAR(id[ny2][nx2]);
          if (b[ny2][nx2] == '-')
            t = NOT(t);
          cs.push_back({a, t});
        }
      }
    }
  }

  auto res = two_satisfiability(m, cs);
  if (!res.first) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    cout << "POSSIBLE" << endl;
    for (int i = 0; i < ps.size(); i++) {
      int x = ps[i].first, y = ps[i].second;
      if (!res.second[i]) {
        if (b[y][x] == '-')
          b[y][x] = '|';
        else
          b[y][x] = '-';
      }
    }
    for (int i = 0; i < R; i++) {
      cout << b[i] << endl;
    }
  }
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    cerr << i << endl;
    cout << "Case #" << i + 1 << ": ";
    solve();
  }
}