#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#else
#define eprintf(...)
#endif

typedef long long ll;
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
    ll n, k;
    cin >> n >> k;
    vector<vector<pair<ll, ll>>> lvl;
    lvl.pb(vector<pair<ll, ll>>(1, mp(n, 1ll)));
    for (int i = 0; i < sz(lvl); i++) {
      ll nexta = -1, cnta = 0, nextb = -1, cntb = 0;
      for (int j = 0; j < sz(lvl[i]); j++) {
        ll cur = lvl[i][j].first, cnt = lvl[i][j].second;
        if (cur == 1)
          continue;
        ll a = (cur - 1) / 2;
        ll b = (cur - 1) - a;
        ll ca = a ? cnt : 0;
        ll cb = cnt;
        if (a > 0) {
          if (nexta == -1 || nexta == a) {
            nexta = a;
            cnta += ca;
          } else {
            nextb = a;
            cntb += ca;
          }
        }
        if (b > 0) {
          if (nexta == -1 || nexta == b) {
            nexta = b;
            cnta += cb;
          } else {
            nextb = b;
            cntb += cb;
          }
        }
      }
      if (nexta != -1)
        lvl.pb(vector<pair<ll, ll>>(1, mp(nexta, cnta)));
      if (nextb != -1)
        lvl[sz(lvl) - 1].pb(mp(nextb, cntb));
    }
    ll ans1 = -1, ans2 = -1;
    for (int i = 0; i < sz(lvl); i++) {
      if (ans1 != -1)
        break;
      for (int j = sz(lvl[i]) - 1; j >= 0; j--) {
        ll cur = lvl[i][j].first, sum = lvl[i][j].second;
        if (k <= sum) {
          ans1 = (cur - 1) / 2;
          ans2 = (cur - 1) - ans1;
          break;
        } else {
          k -= sum;
        }
      }
    }
    cout << ans2 << ' ' << ans1 << endl;
  }
#ifdef LOCAL
  eprintf("Time %.2f\n", (double)clock() / CLOCKS_PER_SEC);
#endif
  return 0;
}