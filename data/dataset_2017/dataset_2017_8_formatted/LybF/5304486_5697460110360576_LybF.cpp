#include <algorithm>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

const double eps = 1e-8;
const double pi = acos(-1.0);

long long need[100];

long long num[100][100];

set<long long> vec[100][100];

void calc(long long num, long long need, int i, int j) {
  for (long long e = 1;; e++) {
    long long now = e * need;
    if (now * 0.9 <= num && now * 1.1 >= num) {
      vec[i][j].insert(e);
    }

    if (now * 0.9 > num) {
      break;
    }
  }
}

int index(int m, int i, int j) { return (i - 1) * m + j; }

const int N = 100;
bool g[N][N], vis[N];
int nx, ny, cx[N], cy[N];
bool dfs(int u) {
  for (int i = 1; i <= ny; i++) {
    if (g[u][i] && !vis[i]) {
      vis[i] = true;
      if (cy[i] == -1 || dfs(cy[i])) {
        cy[i] = u;
        cx[u] = i;
        return true;
      }
    }
  }
  return false;
}
int MaxMatch() {
  int ret = 0;
  memset(cx, -1, sizeof(cx));
  memset(cy, -1, sizeof(cy));
  for (int i = 1; i <= nx; i++) {
    if (cx[i] == -1) {
      memset(vis, 0, sizeof(vis));
      ret += dfs(i);
    }
  }
  return ret;
}

int main() {
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);

  int T;
  cin >> T;

  for (int cas = 1; cas <= T; cas++) {
    int n, p;
    cin >> n >> p;
    for (int i = 1; i <= n; i++) {
      cin >> need[i];
    }
    memset(g, 0, sizeof g);
    nx = p;
    ny = p;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= p; j++) {
        cin >> num[i][j];
        vec[i][j].clear();
      }
    }
    long long ans = 0;

    if (n == 1) {
      for (int j = 1; j <= p; j++) {
        calc(num[1][j], need[1], 1, j);
        if (vec[1][j].size() > 0) {
          ans++;
        }
      }
    } else {
      for (int j = 1; j <= p; j++) {
        calc(num[1][j], need[1], 1, j);
      }
      for (int j = 1; j <= p; j++) {
        calc(num[2][j], need[2], 2, j);
        for (int k = 1; k <= p; k++) {
          for (set<long long>::iterator it = vec[2][j].begin();
               it != vec[2][j].end(); it++) {
            if (vec[1][k].count(*it)) {
              g[j][k] = true;
            }
          }
        }
      }
      ans = MaxMatch();
    }

    cout << "Case #" << cas << ": " << ans << endl;
  }
  return 0;
}
