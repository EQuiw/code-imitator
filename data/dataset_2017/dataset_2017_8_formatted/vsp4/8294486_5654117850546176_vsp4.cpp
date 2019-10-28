#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define cint(d) scanf("%d", &d)
#define cint2(a, b) scanf("%d %d", &a, &b)
#define cint3(a, b, c) scanf("%d %d %d", &a, &b, &c)
#define cint4(a, b, c, d) scanf("%d %d %d %d", &a, &b, &c, &d)

#define clong(d) scanf("%lld", &d)
#define clong2(a, b) scanf("%lld %lld", &a, &b)
#define clong3(a, b, c) scanf("%lld %lld %lld", &a, &b, &c)
#define clong4(a, b, c, d) scanf("%lld %lld %lld %lld", &a, &b, &c, &d)

#define foreach(v, c)                                                          \
  for (__typeof((c).begin()) v = (c).begin(); v != (c).end(); ++v)
#define revforeach(v, c)                                                       \
  for (__typeof((c).rbegin()) v = (c).rbegin(); v != (c).rend(); ++v)
#define ALL(v) (v).begin(), (v).end()

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define fi first
#define se second

typedef long long int slong;
typedef pair<int, int> pii;
typedef pair<slong, slong> pll;
typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    pbds;
typedef set<int>::iterator sit;
typedef map<int, int>::iterator mit;
typedef vector<int>::iterator vit;

#ifdef VSP4
#include "debug.h"
#else
#define debug(args...) // Just strip off all debug tokens
#endif

const int MOD = 1000000007;
#define MODSET(d)                                                              \
  if ((d) >= MOD)                                                              \
    d %= MOD;
#define MODNEGSET(d)                                                           \
  if ((d) < 0)                                                                 \
    d = ((d % MOD) + MOD) % MOD;
#define MODADDSET(d)                                                           \
  if ((d) >= MOD)                                                              \
    d -= MOD;
#define MODADDWHILESET(d)                                                      \
  while ((d) >= MOD)                                                           \
    d -= MOD;

const int MAXN = 100;
const int SQRTN = 550;
const int LOGN = 60;
const int INT_INFINITY = 1001001001;
const int LIMIT = 1e6;

const slong LONG_INFINITY = 1001001001001001001ll;
const slong LONG_LIMIT = 200100100100101ll;

const double DOUBLE_INFINITY = 1e16;

int N, R, O, Y, G, B, V;

int main() {
#ifdef VSP4
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  cout.tie(0);
  cin.tie(0);

  int t, T, i, j;

  cin >> T;

  for (t = 1; t <= T; t++) {
    cin >> N >> R >> O >> Y >> G >> B >> V;

    vector<pair<int, char>> data;

    data.pb(mp(R, 'R'));
    data.pb(mp(Y, 'Y'));
    data.pb(mp(B, 'B'));

    sort(ALL(data), greater<pair<int, char>>());

    cout << "Case #" << t << ": ";

    if (data[0].fi == 1) {
      for (i = 0; i < 3; i++) {
        if (data[i].fi) {
          cout << data[i].se;
        }
      }
    } else {
      if (data[0].fi <= (data[1].fi + data[2].fi)) {
        vector<pair<int, char>> back = data;

        int extra = (data[1].fi + data[2].fi) - data[0].fi;

        int a, b, c;
        a = b = c = 0;

        for (i = 0; i < extra; i++) {
          a++;
          b++;
          c++;
          cout << data[0].se << data[1].se << data[2].se;
        }

        data[1].fi -= extra;
        data[2].fi -= extra;

        for (i = 0; i < data[1].fi; i++) {
          a++;
          b++;
          cout << data[0].se << data[1].se;
        }

        for (i = 0; i < data[2].fi; i++) {
          a++;
          c++;
          cout << data[0].se << data[2].se;
        }

        assert(a == back[0].fi);
        assert(b == back[1].fi);
        assert(c == back[2].fi);
      } else {
        cout << "IMPOSSIBLE";
      }
    }

    cout << endl;
  }

  return 0;
}
