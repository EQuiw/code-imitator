#include <bits/stdc++.h>
using namespace std;

#define li long long int
#define rep(i, to) for (li i = 0; i < ((li)(to)); i++)
#define repp(i, start, to) for (li i = (li)(start); i < ((li)(to)); i++)
#define pb push_back
#define sz(v) ((li)(v).size())
#define bgn(v) ((v).begin())
#define eend(v) ((v).end())
#define allof(v) (v).begin(), (v).end()
#define dodp(v, n) memset(v, (li)n, sizeof(v))
#define bit(n) (1ll << (li)(n))
#define mp(a, b) make_pair(a, b)
#define rin rep(i, n)
#define EPS 1e-12
#define ETOL 1e-8
#define MOD 1000000007
typedef pair<li, li> PI;

#define INF bit(60)

#define DBGP 1

#define idp if (DBGP)
#define F first
#define S second
#define p2(a, b) idp cout << a << "\t" << b << endl
#define p3(a, b, c) idp cout << a << "\t" << b << "\t" << c << endl
#define p4(a, b, c, d)                                                         \
  idp cout << a << "\t" << b << "\t" << c << "\t" << d << endl
#define p5(a, b, c, d, e)                                                      \
  idp cout << a << "\t" << b << "\t" << c << "\t" << d << "\t" << e << endl
#define p6(a, b, c, d, e, f)                                                   \
  idp cout << a << "\t" << b << "\t" << c << "\t" << d << "\t" << e << "\t"    \
           << f << endl
#define p7(a, b, c, d, e, f, g)                                                \
  idp cout << a << "\t" << b << "\t" << c << "\t" << d << "\t" << e << "\t"    \
           << f << "\t" << g << endl
#define p8(a, b, c, d, e, f, g, h)                                             \
  idp cout << a << "\t" << b << "\t" << c << "\t" << d << "\t" << e << "\t"    \
           << f << "\t" << g << "\t" << h << endl
#define p9(a, b, c, d, e, f, g, h, i)                                          \
  idp cout << a << "\t" << b << "\t" << c << "\t" << d << "\t" << e << "\t"    \
           << f << "\t" << g << "\t" << h << "\t" << i << endl
#define p10(a, b, c, d, e, f, g, h, i, j)                                      \
  idp cout << a << "\t" << b << "\t" << c << "\t" << d << "\t" << e << "\t"    \
           << f << "\t" << g << "\t" << h << "\t" << i << "\t" << j << endl
#define foreach(it, v)                                                         \
  for (__typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)
#define p2p(x) idp p2((x).F, (x).S)
#define dump(x, n)                                                             \
  idp {                                                                        \
    rep(i, n) { cout << x[i] << " "; }                                         \
    puts("");                                                                  \
  }
#define dump2(x, n)                                                            \
  idp {                                                                        \
    rep(i, n) { cout << "[" << x[i].F << " , " << x[i].S << "] "; }            \
    puts("");                                                                  \
  }
#define dumpi(x)                                                               \
  idp {                                                                        \
    foreach (it, x) { cout << (*it) << " "; }                                  \
    puts("");                                                                  \
  }
#define dumpi2(x)                                                              \
  idp {                                                                        \
    foreach (it, x) { cout << "[" << (it)->F << " , " << (it)->S << "] "; }    \
    puts("");                                                                  \
  }

#define read2d(a, w, h) rep(i, h) rep(j, w) cin >> a[i][j]
#define dump2d(a, w, h)                                                        \
  rep(i, h) {                                                                  \
    rep(j, w) cout << a[i][j] << " ";                                          \
    puts("");                                                                  \
  }

typedef pair<li, li> PI;

li e[111];
li s[111];
li d[111][111];
li n, q;
li from, to;

// dp[i][j] : i番目の町までj番目の馬で来るときの最小時間
double dp[111][111];
// dp2[i] :
// なんでもいいからi番目の町につくときの最小時間（馬のりかえる時に参照）
double dp2[111];
li sum_distance[111];

inline double calc() {
  // まず2点間距離計算をなんとかする
  sum_distance[0] = 0;
  rep(i, n - 1) { sum_distance[i + 1] = sum_distance[i] + d[i][i + 1]; }
  dp[0][0] = 0;
  dp2[0] = 0;
  repp(i, 1, n) {
    dp2[i] = INF;
    rep(j, i) {
      // j番目の町の馬でここまでくる
      dp[i][j] = INF;
      const li dd = sum_distance[i] - sum_distance[j];
      if (dd <= e[j]) {
        double tmp_part_time = dd * 1.0 / s[j];
        dp[i][j] = dp2[j] + tmp_part_time;
        dp2[i] = min(dp2[i], dp[i][j]);
      }
    }
  }
  return dp2[n - 1];
}

inline void solve() {
  cin >> n >> q;
  rin { cin >> e[i] >> s[i]; }
  rin { rep(j, n) cin >> d[i][j]; }
  rep(i, q) {
    cin >> from >> to;
    printf("%.12f\n", calc());
  }
}

int main() {
  li t;
  cin >> t;
  rep(case_num, t) {
    cout << "Case #" << case_num + 1 << ": ";
    solve();
  }

  return 0;
}