#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;
#define sc(a) scanf("%d", &a)
#define sc2(a, b) scanf("%d%d", &a, &b)
#define sc3(a, b, c) scanf("%d%d%d", &a, &b, &c)
#define scs(a) scanf("%s", a)
#define pri(x) printf("%d\n", x)
#define prie(x) printf("%d ", x)
#define mp make_pair
#define pb push_back
#define BUFF ios::sync_with_stdio(false);
#define db(x) cerr << #x << " == " << x << endl
typedef long long int ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
const ld pi = acos(-1);
const int MOD = 1e9 + 9;
const int N = 50;
int v[3], pack[10][10];
class MaxMatch {
  vi graph[N];
  int match[N], us[N];

public:
  MaxMatch(){};
  void addEdge(int u, int v) { graph[u].pb(v); }
  int dfs(int u) {
    if (us[u])
      return 0;
    us[u] = 1;
    for (int v : graph[u]) {
      if (match[v] == -1 or (dfs(match[v]))) {
        match[v] = u;
        return 1;
      }
    }
    return 0;
  }
  int maxMatch(int n) {
    memset(match, -1, sizeof(match));
    int ret = 0;
    for (int i = 0; i < n; i++) {
      memset(us, 0, sizeof(us));
      ret += dfs(i);
    }
    return ret;
  }
};

ll inf(ll x) { return (9ll * x + 9) / 10ll; }
ll sup(ll x) { return (11ll * x) / 10ll; }
int quantos(int x, int y) {
  for (ll i = 1; i <= 1e6; i++) {
    if (x >= inf(v[0] * i) and x <= sup(v[0] * i)) {
      if (y >= inf(v[1] * i) and y <= sup(v[1] * i))
        return 1;
    }
  }
  return 0;
}
int quantos(int x) {
  for (ll i = 1; i <= 1e6; i++) {
    if (x >= inf(v[0] * i) and x <= sup(v[0] * i)) {
      return 1;
    }
  }
  return 0;
}
void solve() {
  int n, p;
  cin >> n >> p;
  for (int i = 0; i < n; i++)
    cin >> v[i];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < p; j++)
      cin >> pack[i][j];
  if (n == 1) {
    int r = 0;
    for (int j = 0; j < p; j++) {
      r += quantos(pack[0][j]);
    }
    pri(r);
    return;
  } else if (n == 2) {
    MaxMatch g;
    for (int j = 0; j < p; j++)
      for (int k = 0; k < p; k++)
        if (quantos(pack[0][j], pack[1][k]))
          g.addEdge(j, p + k);

    int r = g.maxMatch(p);
    pri(r);
  }
}
int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }
  return 0;
}
