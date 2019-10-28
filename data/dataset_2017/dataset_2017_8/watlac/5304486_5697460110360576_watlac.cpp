#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()

#ifdef LOCAL
#define eprint(x) cerr << #x << " = " << x << endl
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprint(x)
#define eprintf(...)
#endif

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int maxn = 50;
const int maxv = 1e6;

int q[maxn][maxn], r[maxn];
vector<pii> open[maxv + 1], close[maxv + 2];

pii find_range(int have, int need) {
  have *= 10;
  int r = min(have / (9 * need), maxv);
  int l = max((have / (11 * need)) + (have % (11 * need) != 0), 1);
  return mp(l, r);
}

bool good(pii p) {
  return p.first <= p.second;
}

void del_range(vi& v, int id) {
  vi res;
  for (int i = 0; i < sz(v); i++)
    if (v[i] != id)
      res.pb(v[i]);
  v = res;
}

int main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d: ", qq);
    int n, p;
    cin >> n >> p;
    for (int i = 0; i < n; i++)
      cin >> r[i];
    for (int i = 0; i <= maxv; i++) {
      open[i].clear();
      close[i].clear();
    }
    for (int i = 0; i < n; i++)
      for (int j = 0; j < p; j++) {
        cin >> q[i][j];
        pii range = find_range(q[i][j], r[i]);
        if (good(range)) {
          open[range.first].pb(mp(i, j));
          close[range.second + 1].pb(mp(i, j));
        }
      }
    vector<vi> cur(n, vi());
    int ans = 0;
    for (int i = 1; i <= maxv; i++) {
      for (int j = 0; j < sz(close[i]); j++)
        del_range(cur[close[i][j].first], close[i][j].second);
      for (int j = 0; j < sz(open[i]); j++)
        cur[open[i][j].first].pb(open[i][j].second);
      while (true) {
        bool ok = 1;
        for (int j = 0; j < n; j++)
          if (sz(cur[j]) == 0) {
            ok = 0;
            break;
          }
        if (!ok)
          break;
        ans++;
        for (int j = 0; j < n; j++)
          del_range(cur[j], cur[j][0]);
      }
    }
    cout << ans << endl;
  }
#ifdef LOCAL
  eprintf("Time %.2f\n", (double) clock() / CLOCKS_PER_SEC);
#endif
  return 0;
}
