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

inline bool ok_1(li x, li unit) {
  x *= 10;
  unit *= 10;
  li near = x / unit;
  if (x >= unit * near * 9 / 10 && x <= unit * near * 11 / 10) {
    return true;
  }
  ++near;
  if (x >= unit * near * 9 / 10 && x <= unit * near * 11 / 10) {
    return true;
  }
  return false;
}

inline PI get_range(li x, li unit) {
  PI res;
  res.S = (x * 10 / 9) / unit;
  res.F = (x * 10 / 11) / unit;
  if ((x * 10 / 11) % unit > 0)
    res.F++;
  return res;
}

inline bool has_common(PI r1, PI r2) { return r1.S >= r2.F && r2.S >= r1.F; }

inline bool ok_2(PI x, PI unit) {
  PI range1 = get_range(x.F, unit.F);
  PI range2 = get_range(x.S, unit.S);
  // p4(range1.F, range1.S, range2.F, range2.S);
  return has_common(range1, range2);
}

inline void solve() {
  li n, p;
  cin >> n >> p;
  vector<vector<li>> a(n, vector<li>(p));
  vector<li> r(n);
  rin { cin >> r[i]; }
  rep(i, n) { rep(j, p) cin >> a[i][j]; }
  if (n == 1) {
    li res = 0;
    rep(i, p) {
      if (ok_1(a[0][i], r[0])) {
        ++res;
      }
    }
    cout << res << endl;
  } else if (n == 2) {
    li res = 0;
    do {
      li tres = 0;
      rep(i, p) {
        if (ok_2(mp(a[0][i], a[1][i]), mp(r[0], r[1]))) {
          ++tres;
        }
      }
      res = max(res, tres);
    } while (next_permutation(a[1].begin(), a[1].end()));
    cout << res << endl;
  } else {
    cout << 1 << endl;
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