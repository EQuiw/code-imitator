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
typedef long double ld;
typedef vector<vector<ll>> mat;

ld mx = 1e18 + 7;

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
    int n, q;
    cin >> n >> q;
    ll e[105], s[105];
    rep(i, 0, n - 1) cin >> e[i] >> s[i];
    ll d[105][105], dd[105][105];
    rep(i, 0, n - 1) rep(j, 0, n - 1) {
      cin >> d[i][j];
      dd[i][j] = d[i][j];
      if (d[i][j] == -1)
        dd[i][j] = mx;
    }
    rep(i, 0, n - 1) dd[i][i] = 0;
    rep(k, 0, n - 1) rep(i, 0, n - 1) rep(j, 0, n - 1) dd[i][j] =
        min(dd[i][j], dd[i][k] + dd[k][j]);
    int to[105][105] = {0};
    rep(i, 0, n - 1) {
      rep(j, 0, n - 1) {
        if (dd[i][j] > e[i])
          to[i][j] = 0;
        else
          to[i][j] = 1;
      }
    }

    while (q--) {
      int l, r;
      cin >> l >> r;
      l--;
      r--;
      priority_queue<pair<ld, pii>> q;
      ld dis[105][105];
      rep(i, 0, n - 1) rep(j, 0, n - 1) dis[i][j] = mx;
      dis[l][l] = 0;
      q.push(mp(0, mp(l, l)));
      while (!q.empty()) {

        int at = q.top().ss.ff, hor = q.top().ss.ss;
        ld d1 = -q.top().ff;
        q.pop();
        if (d1 > dis[at][hor])
          continue;
        rep(i, 0, n - 1) {
          if (i == at)
            continue;
          if (d[at][i] == -1)
            continue;
          if (to[hor][i] == 0)
            continue;
          ld time = d[at][i];
          time /= (ld)s[hor];
          if (dis[at][hor] + time < dis[i][hor]) {
            dis[i][hor] = dis[at][hor] + time;
            q.push(mp(-dis[i][hor], mp(i, hor)));
          }
        }
        ld d2 = mx;
        rep(i, 0, n - 1) d2 = min(d2, dis[at][i]);
        rep(i, 0, n - 1) {
          if (i == at)
            continue;
          if (d[at][i] == -1)
            continue;
          if (to[at][i] == 0)
            continue;
          ld time = d[at][i];
          time /= (ld)s[at];
          if (d2 + time < dis[i][at]) {
            dis[i][at] = d2 + time;
            q.push(mp(-dis[i][at], mp(i, at)));
          }
        }
      }
      ld ans = mx;
      rep(i, 0, n - 1) ans = min(ans, dis[r][i]);
      cout << fixed << setprecision(10) << ans << " ";
    }
    on;
  }
  return 0;
}
