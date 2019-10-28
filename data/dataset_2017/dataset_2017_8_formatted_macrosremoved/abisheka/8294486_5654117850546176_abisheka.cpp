#include <algorithm>
#include <bitset>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<vector<ll>> mat;

const int MAXN1 = 500000;
const int MAXN2 = 500000;
const int MAXM = 500001;

int n1, n2, edges, last[MAXN1], prev1[MAXM], head[MAXM];
int matching[MAXN2], dist[MAXN1], Q[MAXN1];
bool used[MAXN1], vis[MAXN1];

void init(int _n1, int _n2) {
  n1 = _n1;
  n2 = _n2;
  edges = 0;
  fill(last, last + n1, -1);
}

void addEdge(int u, int v) {
  head[edges] = v;
  prev1[edges] = last[u];
  last[u] = edges++;
}

void bfs() {
  fill(dist, dist + n1, -1);
  int sizeQ = 0;
  for (int u = 0; u < n1; ++u) {
    if (!used[u]) {
      Q[sizeQ++] = u;
      dist[u] = 0;
    }
  }
  for (int i = 0; i < sizeQ; i++) {
    int u1 = Q[i];
    for (int e = last[u1]; e >= 0; e = prev1[e]) {
      int u2 = matching[head[e]];
      if (u2 >= 0 && dist[u2] < 0) {
        dist[u2] = dist[u1] + 1;
        Q[sizeQ++] = u2;
      }
    }
  }
}

bool dfs(int u1) {
  vis[u1] = true;
  for (int e = last[u1]; e >= 0; e = prev1[e]) {
    int v = head[e];
    int u2 = matching[v];
    if (u2 < 0 || !vis[u2] && dist[u2] == dist[u1] + 1 && dfs(u2)) {
      matching[v] = u1;
      used[u1] = true;
      return true;
    }
  }
  return false;
}

int maxMatching() {
  fill(used, used + n1, false);
  fill(matching, matching + n2, -1);
  for (int res = 0;;) {
    bfs();
    fill(vis, vis + n1, false);
    int f = 0;
    for (int u = 0; u < n1; ++u)
      if (!used[u] && dfs(u))
        ++f;
    if (!f)
      return res;
    res += f;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int t, t1 = 0;
  cin >> t;
  while (t--) {
    t1++;
    cout << "Case #";
    cout << t1;
    cout << ": ";
    int n, r, o, y, g, b, v;
    cin >> n >> r >> o >> y >> g >> b >> v;
    for (int i = 0; i <= 1004; i++)
      used[i] = 0, vis[i] = 0, matching[i] = 0, Q[i] = 0, last[i] = 0,
      prev1[i] = 0, head[i] = 0, dist[i] = 0;
    string s;
    map<char, int> m, m1;
    m['r'] = 1;
    m['y'] = 2;
    m['b'] = 4;
    m['o'] = 3;
    m['g'] = 6;
    m['v'] = 5;

    m1['r'] = 0;
    m1['y'] = 1;
    m1['b'] = 2;
    m1['o'] = 3;
    m1['g'] = 4;
    m1['v'] = 5;
    string t = "rybogv";
    for (int i = 0; i <= r - 1; i++)
      s += 'r';
    for (int i = 0; i <= o - 1; i++)
      s += 'o';
    for (int i = 0; i <= y - 1; i++)
      s += 'y';
    for (int i = 0; i <= g - 1; i++)
      s += 'g';
    for (int i = 0; i <= b - 1; i++)
      s += 'b';
    for (int i = 0; i <= v - 1; i++)
      s += 'v';
    init(n, n);
    for (int i = 0; i <= n - 1; i++)
      for (int j = 0; j <= n - 1; j++)
        if ((m[s[i]] & m[s[j]]) == 0)
          addEdge(i, j);
    int mm = maxMatching();
    if (mm != n)
      cout << "IMPOSSIBLE\n";
    else {
      int c[6][6] = {0};
      int c1[6] = {0};
      c1[0] = r;
      c1[1] = y;
      c1[2] = b;
      c1[3] = o;
      c1[4] = g;
      c1[5] = v;
      for (int i = 0; i <= n - 1; i++) {
        c[m1[s[i]]][m1[s[matching[i]]]]++;
      }
      string ans;
      if (r)
        ans = "r", c1[0]--;
      else if (o)
        ans = "o", c1[3]--;
      else if (y)
        ans = "y", c1[1]--;
      else if (b)
        ans = "b", c1[2]--;
      else if (g)
        ans = "g", c1[4]--;
      else if (v)
        ans = "v", c1[5]--;
      for (int i = 0; i <= n - 2; i++) {
        char lst = 'p';
        if (i)
          lst = ans[i - 1];
        int id = -1, mx = -1;
        for (int j = 0; j <= 5; j++) {
          if (t[j] == lst)
            continue;
          if (c[m1[ans[i]]][j] && c1[j]) {
            if (c[m1[ans[i]]][j] > mx) {
              mx = c[m1[ans[i]]][j];
              id = j;
            }
          }
        }
        if (id == -1) {
          c[m1[ans[i]]][m1[lst]]--;
          c1[m1[lst]]--;
          ans += lst;
        } else {
          c[m1[ans[i]]][id]--;
          c1[id]--;
          ans += t[id];
        }
      }
      for (int i = 0; i <= n - 1; i++)
        ans[i] = toupper(ans[i]);
      cout << ans;
      cout << "\n";
    }
  }
  return 0;
}
