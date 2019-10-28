#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef pair<LL, LL> PII;

vector<string> split(const string &s, char c) {
  vector<string> v;
  stringstream ss(s);
  string x;
  while (getline(ss, x, c))
    v.push_back(x);
  return v;
}
void err(vector<string>::iterator it) {}
template <typename T, typename... Args>
void err(vector<string>::iterator it, T a, Args... args) {
  cerr << it->substr((*it)[0] == ' ', it->length()) << " = " << a << ", ";
  err(++it, args...);
}
int T;
const int N = 111;

const LL INF = 0x3f3f3f3f3f3f3f3fll;

int n, q;
LL f[N][N];
LL e[N], s[N];

int main() {
  int cas = 1;
  scanf("%d", &T);

  while (T--) {
    printf("Case #%d:", cas++);

    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
      cin >> e[i] >> s[i];
    }

    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        cin >> f[i][j];
        if (f[i][j] == -1)
          f[i][j] = INF;
      }
    }

    for (int k = 1; k <= n; ++k) {
      for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
          if (f[i][k] + f[k][j] < f[i][j])
            f[i][j] = f[i][k] + f[k][j];
        }
      }
    }

    for (int pp = 1; pp <= q; pp++) {
      int u, v;
      cin >> u >> v;

      double dd[N];
      bool vis[N];
      memset(vis, false, sizeof(vis));
      for (int i = 1; i <= n; ++i)
        dd[i] = 1e20;

      dd[u] = 0;
      vis[u] = true;

      int cur = u;
      while (cur != v) {
        for (int i = 1; i <= n; i++) {
          if (f[cur][i] <= e[cur]) {
            dd[i] = min(dd[i], dd[cur] + 1.0 * f[cur][i] / s[cur]);
          }
        }

        int next = -1;
        for (int i = 1; i <= n; i++) {
          if (vis[i] != true && (next == -1 || dd[next] > dd[i]))
            next = i;
        }

        cur = next;
        vis[cur] = 1;
      }

      printf(" %.10f", dd[v]);
    }
    printf("\n");
  }

  return 0;
}
