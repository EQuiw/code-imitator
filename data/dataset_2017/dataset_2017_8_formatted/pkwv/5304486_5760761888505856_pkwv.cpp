#include <bits/stdc++.h>
#include <stdio.h>

using namespace std;

const int N = 30;

char ma[N][N];
bool ok;
int n, m, lx;
map<char, int> mp;

void get_next(int &x, int &y) {
  ++y;
  if (y > m)
    ++x, y = 1;
}

struct node {
  int x, y, a, b;
  node(int _x = 0, int _y = 0, int _a = 0, int _b = 0) {
    x = _x, y = _y, a = _a, b = _b;
  }
  void add(int _x, int _y) {
    x = min(x, _x), y = min(y, _y);
    a = max(a, _x), b = max(b, _y);
  }
} p[N * N];

bool check(node &nd, char c) {
  for (int i = nd.x; i <= nd.a; i++) {
    for (int j = nd.y; j <= nd.b; j++) {
      if (ma[i][j] == '?' || ma[i][j] == c) {

      } else
        return false;
    }
  }
  return true;
}

void set_ma(node &nd, char c) {
  for (int i = nd.x; i <= nd.a; i++) {
    for (int j = nd.y; j <= nd.b; j++) {
      ma[i][j] = c;
    }
  }
}

void dfs(int x, int y) {
  // printf("%d %d===\n",x, y );
  if (x > n) {
    ok = true;
    return;
  }
  if (ma[x][y] != '?') {
    get_next(x, y);
    dfs(x, y);
    if (ok)
      return;
  } else {
    for (int i = 1; i <= lx; i++) {
      node t = p[i];
      char c = ma[p[i].x][p[i].y];
      p[i].add(x, y);
      if (check(p[i], c)) {
        // printf("%d   %d   %c\n", x,y,c);
        // printf("%d  %d  %d  %d\n", p[i].x,p[i].y,p[i].a,p[i].b);
        set_ma(p[i], c);
        int nx(x), ny(y);
        get_next(nx, ny);
        dfs(nx, ny);
        if (ok)
          return;
        set_ma(p[i], '?');
        p[i] = t;
        set_ma(p[i], c);
      }
      p[i] = t;
    }
  }
}

int main() {
  freopen("/home/zhangyingzhe/Downloads/A-small-attempt0.in", "r", stdin);
  freopen("A-small-attempt0.out", "w", stdout);
  int T;
  scanf("%d", &T);
  for (int ca = 1; ca <= T; ca++) {
    mp.clear();
    lx = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
      scanf("%s", ma[i] + 1);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (ma[i][j] != '?') {
          mp[ma[i][j]] = ++lx;
          p[lx] = node(i, j, i, j);
        }
      }
    }
    ok = false;
    dfs(1, 1);
    printf("Case #%d:\n", ca);
    for (int i = 1; i <= n; i++) {
      printf("%s\n", ma[i] + 1);
    }
  }
  return 0;
}