#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define ft first
#define sd second
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
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;

int main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d: ", qq);
    int n, r, o, y, g, b, v;
    cin >> n >> r >> o >> y >> g >> b >> v;
    vector< pair<int, char> > c;
    c.pb(mp(r, 'R'));
    c.pb(mp(y, 'Y'));
    c.pb(mp(b, 'B'));
    sort(all(c));
    if (c[2].ft > c[0].ft + c[1].ft) {
      cout << "IMPOSSIBLE" << endl;
      continue;
    }
    vi cur;
    for (int i = 0; i < c[0].ft; i++) {
      cur.pb(1);
      cur.pb(0);
    }
    for (int i = 0; i < c[1].ft - c[0].ft; i++)
      cur.pb(1);
    vi upd;
    for (int i = sz(cur) - 1; i >= 0; i--) {
      if (c[2].ft > 0) {
        upd.pb(2);
        c[2].ft--;
      }
      upd.pb(cur[i]);
    }
    for (int i = 0; i < sz(upd); i++)
      cout << c[upd[i]].sd;
    cout << endl;
  }
#ifdef LOCAL
  eprintf("Time %.2f\n", (double) clock() / CLOCKS_PER_SEC);
#endif
  return 0;
}