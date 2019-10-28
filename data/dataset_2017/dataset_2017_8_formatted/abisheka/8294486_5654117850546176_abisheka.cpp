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

#define pb push_back
#define mp make_pair
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define ren(i, a, b) for (int i = a; i >= b; i--)
#define ff first
#define ss second
#define pll pair<long long int, long long int>
#define pii pair<int, int>
#define vll vector<long long int>
#define vii vector<int>
#define gi(n) scanf("%d", &n)
#define gll(n) scanf("%lld", &n)
#define gstr(n) scanf("%s", n)
#define gl(n) cin >> n
#define oi(n) printf("%d", n)
#define oll(n) printf("%lld", n)
#define ostr(n) printf("%s", n)
#define ol(n) cout << n
#define os cout << " "
#define on cout << "\n"
#define o2(a, b) cout << a << " " << b
#define all(n) n.begin(), n.end()
#define present(s, x) (s.find(x) != s.end())
#define cpresent(s, x) (find(all(s), x) != s.end())
#define tr(container, it)                                                      \
  for (__typeof(container.begin()) it = container.begin();                     \
       it != container.end(); it++)
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
  gl(t);
  while (t--) {
    t1++;
    ol("Case #");
    ol(t1);
    ol(": ");
    int n, r, o, y, g, b, v;
    cin >> n >> r >> o >> y >> g >> b >> v;
    rep(i, 0, 1004) used[i] = 0, vis[i] = 0, matching[i] = 0, Q[i] = 0,
                    last[i] = 0, prev1[i] = 0, head[i] = 0, dist[i] = 0;
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
    rep(i, 0, r - 1) s += 'r';
    rep(i, 0, o - 1) s += 'o';
    rep(i, 0, y - 1) s += 'y';
    rep(i, 0, g - 1) s += 'g';
    rep(i, 0, b - 1) s += 'b';
    rep(i, 0, v - 1) s += 'v';
    init(n, n);
    rep(i, 0, n - 1) rep(j, 0, n - 1) if ((m[s[i]] & m[s[j]]) == 0)
        addEdge(i, j);
    int mm = maxMatching();
    if (mm != n)
      ol("IMPOSSIBLE\n");
    else {
      int c[6][6] = {0};
      int c1[6] = {0};
      c1[0] = r;
      c1[1] = y;
      c1[2] = b;
      c1[3] = o;
      c1[4] = g;
      c1[5] = v;
      rep(i, 0, n - 1) { c[m1[s[i]]][m1[s[matching[i]]]]++; }
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
      rep(i, 0, n - 2) {
        char lst = 'p';
        if (i)
          lst = ans[i - 1];
        int id = -1, mx = -1;
        rep(j, 0, 5) {
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
      rep(i, 0, n - 1) ans[i] = toupper(ans[i]);
      ol(ans);
      on;
    }
  }
  return 0;
}
