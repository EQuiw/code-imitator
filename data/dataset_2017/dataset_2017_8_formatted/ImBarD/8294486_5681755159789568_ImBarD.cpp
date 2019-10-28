#include <algorithm>
#include <cstring>
#include <ctype.h>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef std::vector<ld> vld;
typedef std::vector<vld> vvld;
typedef std::vector<int> vi;
typedef std::vector<bool> vb;
typedef std::vector<string> vs;
typedef std::vector<double> vd;
typedef std::vector<long long> vll;
typedef std::vector<std::vector<int>> vvi;
typedef vector<vvi> vvvi;
typedef vector<vll> vvll;
typedef std::vector<std::pair<int, int>> vpi;
typedef vector<vpi> vvpi;
typedef std::pair<int, int> pi;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;

const long long mod = 1000000007;

#define all(c) (c).begin(), (c).end()
#define sz(c) (int)(c).size()
#define forn(i, a, b) for (int i = a; i < b; i++)

#define pb push_back
#define mp make_pair

int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "rt", stdin);
  freopen("output.txt", "wt", stdout);
#endif
  int t;
  scanf("%d", &t);
  forn(iad, 0, t) {
    printf("Case #%d:", iad + 1);
    int n, q;
    scanf("%d %d", &n, &q);
    vll st(n), sp(n);
    forn(i, 0, n) { scanf("%lld %lld", &st[i], &sp[i]); }
    vvll d(n, vll(n, 0));
    forn(i, 0, n) forn(j, 0, n) scanf("%lld", &d[i][j]);
    const ll INF = 1e18;
    forn(i, 0, n) forn(j, 0, n) if (d[i][j] == -1) d[i][j] = INF;
    for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
          if (d[i][k] < INF && d[k][j] < INF)
            d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    const ld INF2 = 1e18;
    vvld dist(n, vld(n, 2 * INF2));
    forn(i, 0, n) forn(j, 0, n) {
      if (d[i][j] <= st[i])
        dist[i][j] = (ld)d[i][j] / (ld)sp[i];
    }
    for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
          if (dist[i][k] < INF2 && dist[k][j] < INF2)
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    forn(i, 0, q) {
      int u, v;
      scanf("%d %d", &u, &v);
      u--;
      v--;
      printf(" %.10lf", (double)dist[u][v]);
    }
    printf("\n");
  }
}
